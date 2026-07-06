#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <setjmp.h>

static sigjmp_buf jump_buffer;
static volatile sig_atomic_t buffer_overflow_detected = 0;

static void segfault_handler(int sig) {
    buffer_overflow_detected = 1;
    siglongjmp(jump_buffer, 1);
}

START_TEST(test_lockfile_buffer_overflow)
{
    // Invariant: Buffer reads from lock files never exceed declared length
    // Lock file format contains username and program name that get sprintf'd
    
    const char *oversized_payloads[] = {
        // Exact exploit: 2KB username (10x typical buffer of ~200 bytes)
        NULL,
        // Boundary: exactly 256 bytes (common buffer size)
        NULL,
        // Valid input: normal short username
        "validuser"
    };
    
    // Generate oversized strings
    char payload_2k[2048];
    memset(payload_2k, 'A', sizeof(payload_2k) - 1);
    payload_2k[sizeof(payload_2k) - 1] = '\0';
    oversized_payloads[0] = payload_2k;
    
    char payload_256[257];
    memset(payload_256, 'B', 256);
    payload_256[256] = '\0';
    oversized_payloads[1] = payload_256;
    
    int num_payloads = sizeof(oversized_payloads) / sizeof(oversized_payloads[0]);
    
    for (int i = 0; i < num_payloads; i++) {
        // Create a malicious lock file with oversized username
        char lockfile_path[] = "/tmp/nano_test_lock_XXXXXX";
        int fd = mkstemp(lockfile_path);
        ck_assert_int_ge(fd, 0);
        
        // Write lock file content: nano lock format is "pid program user"
        char lock_content[4096];
        snprintf(lock_content, sizeof(lock_content), "%d %s %s\n", 
                 getpid(), oversized_payloads[i], oversized_payloads[i]);
        write(fd, lock_content, strlen(lock_content));
        close(fd);
        
        // Set up signal handler to catch buffer overflow crashes
        struct sigaction sa, old_sa;
        sa.sa_handler = segfault_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        sigaction(SIGSEGV, &sa, &old_sa);
        sigaction(SIGBUS, &sa, NULL);
        
        buffer_overflow_detected = 0;
        
        if (sigsetjmp(jump_buffer, 1) == 0) {
            // Attempt to read the lock file - if vulnerable, this will overflow
            FILE *f = fopen(lockfile_path, "r");
            if (f) {
                char buf[4096];
                if (fgets(buf, sizeof(buf), f)) {
                    // Simulate the vulnerable sprintf pattern
                    char promptstr[256];
                    char lockuser[4096], lockprog[4096], pidstring[32];
                    sscanf(buf, "%31s %4095s %4095s", pidstring, lockprog, lockuser);
                    
                    // This is where the vulnerability would trigger
                    // Safe code should truncate or reject oversized input
                    size_t needed = strlen(lockuser) + strlen(lockprog) + strlen(pidstring) + 100;
                    ck_assert_msg(needed <= sizeof(promptstr) || i == 2,
                        "Oversized input should be truncated or rejected, not passed through");
                }
                fclose(f);
            }
        }
        
        sigaction(SIGSEGV, &old_sa, NULL);
        ck_assert_msg(!buffer_overflow_detected, 
            "Buffer overflow detected with payload %d", i);
        
        unlink(lockfile_path);
    }
}
END_TEST

Suite *security_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Security");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_lockfile_buffer_overflow);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;