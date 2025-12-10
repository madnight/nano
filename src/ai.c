/**************************************************************************
 *   ai.c  --  Helpers for AI-backed commands in Milli.                   *
 **************************************************************************/

#include "prototypes.h"

#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static ai_config ai_conf = {0};

static char *trim(char *s)
{
	char *end;

	while (isspace((unsigned char)*s))
		s++;

	if (*s == '\0')
		return s;

	end = s + strlen(s) - 1;
	while (end > s && isspace((unsigned char)*end))
		end--;

	end[1] = '\0';
	return s;
}

static bool parse_double(const char *val, double *out)
{
	char *endptr;
	double v = strtod(val, &endptr);
	if (endptr == val || *endptr != '\0')
		return FALSE;
	*out = v;
	return TRUE;
}

static bool parse_long(const char *val, long *out)
{
	char *endptr;
	long v = strtol(val, &endptr, 10);
	if (endptr == val || *endptr != '\0')
		return FALSE;
	*out = v;
	return TRUE;
}

static bool load_ai_config_file(char **errmsg)
{
	FILE *fp;
	char line[1024];
	char *configpath;

	get_homedir();
	if (homedir == NULL) {
		if (errmsg)
			*errmsg = copy_of(_("Could not determine HOME for ~/.milli.config"));
		return FALSE;
	}

	configpath = concatenate(homedir, "/.milli.config");
	fp = fopen(configpath, "r");
	if (fp == NULL) {
		if (errmsg) {
			size_t len = strlen(configpath) + 64;
			char *buf = nmalloc(len);
			snprintf(buf, len, _("Missing AI config at %s"), configpath);
			*errmsg = buf;
		}
		free(configpath);
		return FALSE;
	}
	free(configpath);

	while (fgets(line, sizeof(line), fp) != NULL) {
		char *eq, *key, *val;

		if (line[0] == '#' || line[0] == ';')
			continue;

		eq = strchr(line, '=');
		if (eq == NULL)
			continue;

		*eq = '\0';
		key = trim(line);
		val = trim(eq + 1);

		if (*key == '\0')
			continue;

		if (strcmp(key, "base_url") == 0)
			ai_conf.base_url = mallocstrcpy(ai_conf.base_url, val);
		else if (strcmp(key, "responses_endpoint") == 0)
			ai_conf.responses_endpoint = mallocstrcpy(ai_conf.responses_endpoint, val);
		else if (strcmp(key, "models_endpoint") == 0)
			ai_conf.models_endpoint = mallocstrcpy(ai_conf.models_endpoint, val);
		else if (strcmp(key, "model") == 0)
			ai_conf.model = mallocstrcpy(ai_conf.model, val);
		else if (strcmp(key, "api_key") == 0)
			ai_conf.api_key = mallocstrcpy(ai_conf.api_key, val);
		else if (strcmp(key, "temperature") == 0)
			parse_double(val, &ai_conf.temperature);
		else if (strcmp(key, "timeout_ms") == 0)
			parse_long(val, &ai_conf.timeout_ms);
	}

	fclose(fp);

	if (ai_conf.base_url == NULL || ai_conf.responses_endpoint == NULL ||
			ai_conf.model == NULL) {
		if (errmsg)
			*errmsg = copy_of(_("AI config missing base_url, responses_endpoint, or model"));
		return FALSE;
	}

	if (ai_conf.api_key == NULL)
		ai_conf.api_key = mallocstrcpy(ai_conf.api_key, "lm-studio");
	if (ai_conf.temperature == 0.0)
		ai_conf.temperature = 0.2;
	if (ai_conf.timeout_ms == 0)
		ai_conf.timeout_ms = 60000;

	ai_conf.loaded = TRUE;
	return TRUE;
}

bool ensure_ai_config_loaded(char **errmsg)
{
	if (ai_conf.loaded)
		return TRUE;

	return load_ai_config_file(errmsg);
}

static char *join_url(const char *base, const char *endpoint)
{
	size_t baselen = strlen(base);
	size_t endlen = strlen(endpoint);
	bool base_has_slash = (baselen > 0 && base[baselen - 1] == '/');
	bool end_has_slash = (endlen > 0 && endpoint[0] == '/');
	size_t extra = (base_has_slash && end_has_slash) ? 0 :
					(!base_has_slash && !end_has_slash) ? 1 : 0;
	char *combined = nmalloc(baselen + endlen + extra + 1);

	strcpy(combined, base);
	if (extra)
		strcat(combined, "/");
	strcat(combined, end_has_slash ? endpoint + 1 : endpoint);

	return combined;
}

static char *json_escape(const char *text)
{
	size_t len = 0;
	const char *p;
	char *out, *o;

	for (p = text; *p; p++) {
		switch (*p) {
			case '\\':
			case '"':
				len += 2;
				break;
			case '\n':
			case '\r':
			case '\t':
				len += 2;
				break;
			default:
				len++;
		}
	}

	out = nmalloc(len + 1);
	o = out;
	for (p = text; *p; p++) {
		switch (*p) {
			case '\\': *o++ = '\\'; *o++ = '\\'; break;
			case '"':  *o++ = '\\'; *o++ = '"';  break;
			case '\n': *o++ = '\\'; *o++ = 'n';  break;
			case '\r': *o++ = '\\'; *o++ = 'r';  break;
			case '\t': *o++ = '\\'; *o++ = 't';  break;
			default:   *o++ = *p;               break;
		}
	}
	*o = '\0';
	return out;
}

static char *build_payload(const char *prompt, const char *selection)
{
	char *escaped_body, *payload;
	size_t len;

	if (selection != NULL && *selection != '\0') {
		char *combined;
		size_t combo_len = strlen(prompt) + strlen(selection) + 64;
		combined = nmalloc(combo_len);
		snprintf(combined, combo_len,
			"User prompt:\n%s\n\nSelection:\n%s", prompt, selection);
		escaped_body = json_escape(combined);
		free(combined);
	} else {
		escaped_body = json_escape(prompt);
	}

	len = strlen(escaped_body) + strlen(ai_conf.model) + 128;
	payload = nmalloc(len);
	snprintf(payload, len,
		"{\"model\":\"%s\",\"input\":\"%s\",\"temperature\":%.3f}",
		ai_conf.model, escaped_body, ai_conf.temperature);

	free(escaped_body);
	return payload;
}

static bool write_payload_to_file(const char *payload, char **path_out)
{
	char template[] = "/tmp/milli-ai-XXXXXX";
	int fd = mkstemp(template);
	size_t total = 0, len = strlen(payload);

	if (fd < 0)
		return FALSE;

	while (total < len) {
		ssize_t written = write(fd, payload + total, len - total);
		if (written <= 0) {
			close(fd);
			unlink(template);
			return FALSE;
		}
		total += (size_t)written;
	}
	close(fd);
	*path_out = mallocstrcpy(NULL, template);
	return TRUE;
}

static char *read_stream(FILE *fp)
{
	size_t cap = 4096;
	size_t len = 0;
	char *buf = nmalloc(cap);
	int c;

	while ((c = fgetc(fp)) != EOF) {
		if (len + 1 >= cap) {
			cap *= 2;
			buf = nrealloc(buf, cap);
		}
		buf[len++] = (char)c;
	}
	buf[len] = '\0';
	return buf;
}

static char *extract_output_text(const char *body)
{
	const char *found = strstr(body, "\"output_text\"");
	const char *start, *end;

	if (found == NULL)
		found = strstr(body, "\"text\"");

	if (found == NULL)
		return copy_of(body);

	found = strchr(found, ':');
	if (found == NULL)
		return copy_of(body);

	found++;
	while (*found && (*found == ' ' || *found == '\t'))
		found++;

	if (*found != '"')
		return copy_of(body);

	start = ++found;
	while (*found && *found != '"') {
		if (*found == '\\' && *(found + 1) != '\0')
			found++;
		found++;
	}

	end = found;
	if (*end != '"')
		return copy_of(body);

	{
		size_t outlen = (size_t)(end - start);
		char *out = nmalloc(outlen + 1);
		size_t i = 0;
		for (const char *p = start; p < end; p++) {
			if (*p == '\\' && (p + 1) < end) {
				p++;
				switch (*p) {
					case 'n': out[i++] = '\n'; break;
					case 'r': out[i++] = '\r'; break;
					case 't': out[i++] = '\t'; break;
					case '\\': out[i++] = '\\'; break;
					case '"': out[i++] = '"'; break;
					default: out[i++] = *p; break;
				}
			} else
				out[i++] = *p;
		}
		out[i] = '\0';
		return out;
	}
}

bool ai_generate_text(const char *user_prompt, const char *selection,
				char **output_text, char **errmsg)
{
	char *payload = NULL, *payload_path = NULL, *command = NULL;
	char *url = NULL, *body = NULL;
	FILE *pipe = NULL;
	double timeout_s;
	bool ok = FALSE;

	if (!ensure_ai_config_loaded(errmsg))
		goto cleanup;

	payload = build_payload(user_prompt, selection);
	if (!write_payload_to_file(payload, &payload_path)) {
		if (errmsg)
			*errmsg = copy_of(_("Could not write AI payload to temp file"));
		goto cleanup;
	}

	url = join_url(ai_conf.base_url, ai_conf.responses_endpoint);
	timeout_s = (ai_conf.timeout_ms > 0) ? ((double)ai_conf.timeout_ms / 1000.0) : 60.0;

	{
		size_t cmdlen = strlen(url) + strlen(payload_path) +
				(ai_conf.api_key ? strlen(ai_conf.api_key) : 0) + 256;
		command = nmalloc(cmdlen);
		snprintf(command, cmdlen,
			"curl -sS --fail --max-time %.3f "
			"-H \"Content-Type: application/json\" "
			"-H \"Authorization: Bearer %s\" "
			"-X POST \"%s\" --data-binary @\"%s\"",
			timeout_s,
			(ai_conf.api_key ? ai_conf.api_key : "lm-studio"),
			url, payload_path);
	}

	pipe = popen(command, "r");
	if (pipe == NULL) {
		if (errmsg)
			*errmsg = copy_of(_("Could not invoke curl for AI request"));
		goto cleanup;
	}

	body = read_stream(pipe);
	if (pclose(pipe) != 0) {
		if (errmsg) {
			size_t elen = strlen(body) + 64;
			char *buf = nmalloc(elen);
			snprintf(buf, elen, _("AI call failed: %s"), body);
			*errmsg = buf;
		}
		goto cleanup;
	}

	*output_text = extract_output_text(body);
	ok = TRUE;

cleanup:
	free(payload);
	free(payload_path);
	free(command);
	free(url);
	free(body);
	return ok;
}
