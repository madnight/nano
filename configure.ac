# Configuration for GNU nano - a small and user-friendly text editor
#
# Copyright (C) 1999-2011, 2013-2025 Free Software Foundation, Inc.
# Copyright (C) 2014, 2017 Mike Frysinger
#
# GNU nano is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published
# by the Free Software Foundation, either version 3 of the License,
# or (at your option) any later version.
#
# GNU nano is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see https://www.gnu.org/licenses/.

AC_INIT([GNU nano], [8.5], [nano-devel@gnu.org], [nano])
AC_CONFIG_SRCDIR([src/nano.c])
AC_CANONICAL_HOST
AM_INIT_AUTOMAKE([1.14])
AM_MAINTAINER_MODE([enable])
AC_CONFIG_HEADERS([config.h])

dnl Make sure the ONCE macros are available.

AC_PREREQ([2.69])

dnl Lie about gnulib features we don't use to speed up & shrink down.

gl_cv_func_printf_directive_n=yes
gl_cv_func_printf_infinite_long_double=yes
gl_cv_func_printf_long_double=yes
gl_cv_func_snprintf_directive_n=yes
gl_cv_glob_lists_symlinks=yes

dnl Checks for programs.

AC_USE_SYSTEM_EXTENSIONS
AC_PROG_CC
gl_EARLY
gl_INIT
AC_PROG_LN_S
AC_SEARCH_LIBS([strerror], [cposix])
AC_SYS_LARGEFILE
PKG_PROG_PKG_CONFIG

dnl Internationalization macros.

AM_GNU_GETTEXT_VERSION([0.20])
AM_GNU_GETTEXT([external], [need-ngettext])
AM_CONDITIONAL(USE_NLS, test x$USE_NLS = xyes)

dnl Data location.

pkgdatadir=${datadir}/${PACKAGE}
AC_DEFINE_DIR([PKGDATADIR], [pkgdatadir], [Where data are placed to.])

dnl Whether this is a git repository.

AC_MSG_CHECKING([whether building from git])
if test -f "$srcdir/roll-a-release.sh" ; then
	AC_MSG_RESULT([yes])
	from_git=yes
else
	AC_MSG_RESULT([no])
	from_git=no
fi
AM_CONDITIONAL(BUILDING_FROM_GIT, test x$from_git = xyes)

dnl Checks for pkg-config and gettext when building from git.

if test x$from_git = xyes; then
	if test ! -f $(aclocal --print-ac-dir)/pkg.m4; then
		AC_MSG_ERROR([
  *** The pkg.m4 macros are missing.
  *** The pkg-config package needs to be installed when building from git.
  *** After fixing this problem, rerun ./autogen.sh.])
	fi
	if test "$ac_cv_path_MSGFMT" = ":"; then
		AC_MSG_ERROR([
  *** The msgfmt program is missing.
  *** The gettext package needs to be installed when building from git.])
	fi
fi

dnl Checks for header files.

AC_CHECK_HEADERS(libintl.h limits.h pwd.h termios.h sys/param.h)

dnl Checks for options.

AC_ARG_ENABLE(browser,
AS_HELP_STRING([--disable-browser], [Disable the built-in file browser]))
if test "x$enable_tiny" = xyes; then
	if test "x$enable_browser" != xyes; then
		enable_browser=no
	fi
fi
if test "x$enable_browser" != xno; then
	AC_DEFINE(ENABLE_BROWSER, 1, [Define this to enable the built-in file browser.])
fi

AC_ARG_ENABLE(color,
AS_HELP_STRING([--disable-color], [Disable color and syntax highlighting]))
if test "x$enable_tiny" = xyes; then
	if test "x$enable_color" = xyes; then
		if test "x$enable_nanorc" != xyes; then
			AC_MSG_ERROR([
  ***  --enable-color needs --enable-nanorc to work])
		fi
	else
		enable_color=no
	fi
fi
if test "x$enable_nanorc" = xno; then
	if test "x$enable_color" = xyes; then
		AC_MSG_ERROR([
  ***  --enable-color cannot work with --disable-nanorc])
	else
		# Disabling nanorc silently disables color support.
		enable_color=no
	fi
fi
if test "x$enable_color" != xno; then
	AC_DEFINE(ENABLE_COLOR, 1, [Define this to have syntax highlighting.])
	color_support=yes
fi

AC_ARG_ENABLE(comment,
AS_HELP_STRING([--disable-comment], [Disable the comment/uncomment function]))
if test "x$enable_tiny" = xyes; then
	if test "x$enable_comment" = xyes; then
		AC_MSG_ERROR([
  ***  --enable-comment cannot work with --enable-tiny])
	else
		enable_comment=no
	fi
fi
if test "x$enable_comment" != xno; then
	AC_DEFINE(ENABLE_COMMENT, 1, [Define this to enable the comment/uncomment function.])
fi

AC_ARG_ENABLE(extra,
AS_HELP_STRING([--disable-extra], [Disable the Easter egg]))
if test "x$enable_tiny" = xyes; then
	if test "x$enable_extra" != xyes; then
		enable_extra=no
	fi
fi
if test "x$enable_extra" != xno; then
	AC_DEFINE(ENABLE_EXTRA, 1, [Define this to have an Easter egg.])
fi

AC_ARG_ENABLE(formatter,
AS_HELP_STRING([--disable-formatter], [Disable the formatting tool]))
if test "x$enable_tiny" = xyes; then
	if test "x$enable_formatter" = xyes; then
		if test "x$enable_color" != xyes; then
			AC_MSG_ERROR([
  ***  --enable-formatter needs both --enable-color and --enable-nanorc to work])
		fi
	else
		enable_formatter=no
	fi
fi
if test "x$enable_color" = xno; then
	if test "x$enable_formatter" = xyes; then
		AC_MSG_ERROR([
  ***  --enable-formatter cannot work with --disable-color nor --disable-nanorc])
	else
		enable_formatter=no
	fi
fi
if test "x$enable_formatter" != xno; then
	AC_DEFINE(ENABLE_FORMATTER, 1, [Define this to have access to a formatter.])
fi

AC_ARG_ENABLE(help,
AS_HELP_STRING([--disable-help], [Disable the built-in help texts]))
if test "x$enable_tiny" = xyes; then
	if test "x$enable_help" = xyes; then
		if test "x$enable_multibuffer" != xyes; then
			AC_MSG_ERROR([
  ***  --enable-help needs --enable-multibuffer to work])
		fi
	else
		enable_help=no
	fi
fi
if test "x$enable_multibuffer" = xno; then
	if test "x$enable_help" = xyes; then
		AC_MSG_ERROR([
  ***  --enable-help cannot work with --disable-multibuffer])
	else
		# Disabling multibuffer silently disables the help texts.
		enable_help=no
	fi
fi
if test "x$enable_help" != xno; then
	AC_DEFINE(ENABLE_HELP, 1, [Define this to enable the Ctrl+G help texts.])
fi

AC_ARG_ENABLE(histories,
AS_HELP_STRING([--disable-histories], [Disable search and position histories]))
if test "x$enable_tiny" = xyes; then
	if test "x$enable_histories" != xyes; then
		enable_histories=no
	fi
fi
if test "x$enable_histories" != xno; then
	AC_DEFINE(ENABLE_HISTORIES, 1, [Define this to have search and position histories.])
fi

AC_ARG_ENABLE(justify,
AS_HELP_STRING([--disable-justify], [Disable the justify/unjustify functions]))
if test "x$enable_tiny" = xyes; then
	if test "x$enable_justify" != xyes; then
		enable_justify=no
	fi
fi
if test "x$enable_justify" != xno; then
	AC_DEFINE(ENABLE_JUSTIFY, 1, [Define this to have the routines for justifying.])
fi

AC_ARG_ENABLE(libmagic,
AS_HELP_STRING([--disable-libmagic], [Disable detection of file types via libmagic]))
if test "x$enable_libmagic" = xyes; then
	if test "x$enable_tiny" = xyes; then
		if test "x$enable_color" != xyes; then
			AC_MSG_ERROR([
  ***  --enable-libmagic needs both --enable-color and --enable-nanorc to work])
		fi
	fi
	if test "x$enable_color" = xno; then
		AC_MSG_ERROR([
  ***  --enable-libmagic cannot work with --disable-color nor --disable-nanorc])
	fi
fi

AC_ARG_ENABLE(linter,
AS_HELP_STRING([--disable-linter], [Disable the linting tool]))
if test "x$enable_tiny" = xyes; then
	if test "x$enable_linter" = xyes; then
		if test "x$enable_color" != xyes; then
			AC_MSG_ERROR([
  ***  --enable-linter needs both --enable-color and --enable-nanorc to work])
		fi
	else
		enable_linter=no
	fi
fi
if test "x$enable_color" = xno; then
	if test "x$enable_linter" = xyes; then
		AC_MSG_ERROR([
  ***  --enable-linter cannot work with --disable-color nor --disable-nanorc])
	else
		enable_linter=no
	fi
fi
if test "x$enable_linter" != xno; then
	AC_DEFINE(ENABLE_LINTER, 1, [Define this to have access to a linter.])
fi

AC_ARG_ENABLE(linenumbers,
AS_HELP_STRING([--disable-linenumbers], [Disable line numbering]))
if test "x$enable_tiny" = xyes; then
	if test "x$enable_linenumbers" != xyes; then
		enable_linenumbers=no
	fi
fi
if test "x$enable_linenumbers" != xno; then
	AC_DEFINE(ENABLE_LINENUMBERS, 1, [Define this to enable line numbering.])
fi

AC_ARG_ENABLE(mouse,
AS_HELP_STRING([--disable-mouse], [Disable mouse support]))
if test "x$enable_tiny" = xyes; then
	if test "x$enable_mouse" != xyes; then
		enable_mouse=no
	fi
fi
if test "x$enable_mouse" != xno; then
	AC_DEFINE(ENABLE_MOUSE, 1, [Define this to enable mouse support.])
fi

AC_ARG_ENABLE(multibuffer,
AS_HELP_STRING([--disable-multibuffer], [Disable multiple file buffers]))
if test "x$enable_tiny" = xyes; then
	if test "x$enable_multibuffer" != xyes; then
		enable_multibuffer=no
	fi
fi
if test "x$enable_multibuffer" != xno; then
	AC_DEFINE(ENABLE_MULTIBUFFER, 1, [Define this to enable multiple file buffers.])
fi

AC_ARG_ENABLE(nanorc,
AS_HELP_STRING([--disable-nanorc], [Disable the use of .nanorc files]))
if test "x$enable_tiny" = xyes; then
	if test "x$enable_nanorc" != xyes; then
		enable_nanorc=no
	fi
fi
if test "x$enable_nanorc" != xno; then
	AC_DEFINE(ENABLE_NANORC, 1, [Define this to enable the use of .nanorc files.])
	nanorc_support=yes
fi

AC_ARG_ENABLE(operatingdir,
AS_HELP_STRING([--disable-operatingdir], [Disable the setting of an operating directory]))
if test "x$enable_tiny" = xyes; then
	if test "x$enable_operatingdir" != xyes; then
		enable_operatingdir=no
	fi
fi
if test "x$enable_operatingdir" != xno; then
	AC_DEFINE(ENABLE_OPERATINGDIR, 1, [Define this to allow setting an operating directory (a chroot of sorts).])
fi

AC_ARG_ENABLE(speller,
AS_HELP_STRING([--disable-speller], [Disable the spell-checking tool]))
if test "x$enable_tiny" = xyes; then
	if test "x$enable_speller" != xyes; then
		enable_speller=no
	fi
fi
if test "x$enable_speller" != xno; then
	AC_DEFINE(ENABLE_SPELLER, 1, [Define this to have access to a spell checker.])
fi

AC_ARG_ENABLE(tabcomp,
AS_HELP_STRING([--disable-tabcomp], [Disable the tab-completion functions]))
if test "x$enable_tiny" = xyes; then
	if test "x$enable_tabcomp" != xyes; then
		enable_tabcomp=no
	fi
fi
if test "x$enable_tabcomp" != xno; then
	AC_DEFINE(ENABLE_TABCOMP, 1, [Define this to have tab completion for filenames and search strings.])
fi

AC_ARG_ENABLE(wordcomp,
AS_HELP_STRING([--disable-wordcomp], [Disable the word-completion function]))
if test "x$enable_tiny" = xyes; then
	if test "x$enable_wordcomp" = xyes; then
		AC_MSG_ERROR([
  ***  --enable-wordcomp cannot work with --enable-tiny])
	else
		enable_wordcomp=no
	fi
fi
if test "x$enable_wordcomp" != xno; then
	AC_DEFINE(ENABLE_WORDCOMPLETION, 1, [Define this to enable the word-completion function.])
fi

AC_ARG_ENABLE(wrapping,
AS_HELP_STRING([--disable-wrapping], [Disable all hard-wrapping of text]))
if test "x$enable_tiny" = xyes; then
	if test "x$enable_wrapping" != xyes; then
		enable_wrapping=no
	fi
fi
if test "x$enable_wrapping" != xno; then
	AC_DEFINE(ENABLE_WRAPPING, 1, [Define this to have hard text wrapping.])
fi

AC_ARG_ENABLE(debug,
AS_HELP_STRING([--enable-debug], [Enable debugging (disabled by default)]))
if test "x$enable_debug" = xyes; then
	AC_DEFINE(DEBUG, 1, [Define this to enable debug messages and abortion on failing asserts.])
else
	AC_DEFINE(NDEBUG, 1, [Shut up assert warnings :-)])
fi

AC_ARG_ENABLE(tiny,
AS_HELP_STRING([--enable-tiny], [Disable features for the sake of size]))
if test "x$enable_tiny" = xyes; then
	AC_DEFINE(NANO_TINY, 1, [Define this to make the nano executable as small as possible.])
	if test "x$enable_libmagic" != xyes; then
		enable_libmagic=no
	fi
fi

AM_CONDITIONAL(USE_COLOR, test x$color_support = xyes)
AM_CONDITIONAL(USE_NANORC, test x$nanorc_support = xyes)

AC_MSG_CHECKING([whether to enable UTF-8 support])
AC_ARG_ENABLE(utf8, AS_HELP_STRING([--enable-utf8], [Enable UTF-8 support]))
AC_MSG_RESULT(${enable_utf8:-auto})

AC_ARG_ENABLE(altrcname,
AS_HELP_STRING([--enable-altrcname], [Specify an alternate rcfile name (default: .nanorc)]),
[if test x$enableval != no; then
	AC_DEFINE_UNQUOTED(RCFILE_NAME, "$enableval", [Specify an alternate rcfile name (default: .nanorc).]) rcfilename=$enableval
fi])

dnl Checks for functions.

if test "x$enable_utf8" != xno; then
	AC_CHECK_FUNCS(iswalpha iswalnum iswpunct mbstowcs wctomb)
fi

AC_CHECK_FUNCS_ONCE(chmod chown fchmod fchown flockfile funlockfile
                    fork fsync geteuid pipe wait waitpid)

dnl Checks for available flags.

AX_CHECK_COMPILE_FLAG([-Wall], [CFLAGS="$CFLAGS -Wall"], [], [])

dnl Checks for libraries.

if eval "test x$CURSES_LIB_NAME = x"; then
	if test "x$enable_utf8" != xno; then
		PKG_CHECK_MODULES([NCURSESW], [ncursesw], [
			CURSES_LIB=$NCURSESW_LIBS
			CPPFLAGS="$NCURSESW_CFLAGS $CPPFLAGS"
			CURSES_LIB_NAME=ncursesw
			CURSES_LIB_WIDE=yes
		], [:])
	else
		PKG_CHECK_MODULES([NCURSES], [ncurses], [
			CURSES_LIB=$NCURSES_LIBS
			CPPFLAGS="$NCURSES_CFLAGS $CPPFLAGS"
			CURSES_LIB_NAME=ncurses
		], [:])
	fi
fi

if eval "test x$CURSES_LIB_NAME = x"; then
	AC_CHECK_HEADERS(ncurses.h)

	if test "x$enable_utf8" != xno; then
		OLDLIBS="$LIBS"
		AC_CHECK_TOOL(NCURSESW_CONFIG, ncursesw5-config, no)
		if test "x$NCURSESW_CONFIG" != xno; then
			CURSES_LIB=`$NCURSESW_CONFIG --libs`
			LIBS="$CURSES_LIB $LIBS"
			CPPFLAGS="`$NCURSESW_CONFIG --cflags` $CPPFLAGS"
			AC_CHECK_LIB(ncursesw, wget_wch, [CURSES_LIB_NAME=ncursesw CURSES_LIB_WIDE=yes])
		else
			AC_CHECK_LIB(ncursesw, wget_wch, [CURSES_LIB="-lncursesw" CURSES_LIB_NAME=ncursesw CURSES_LIB_WIDE=yes])
		fi
		LIBS="$OLDLIBS"
	fi

	if eval "test x$CURSES_LIB_NAME = x"; then
		AC_CHECK_LIB(ncurses, initscr, [CURSES_LIB="-lncurses" CURSES_LIB_NAME=ncurses])
	fi
fi

if eval "test x$CURSES_LIB_NAME = x"; then
	AC_CHECK_HEADERS(curses.h)

	if test "x$enable_utf8" != xno; then
		AC_CHECK_LIB(curses, wget_wch, [CURSES_LIB="-lcurses" CURSES_LIB_NAME=curses CURSES_LIB_WIDE=yes])
	fi

	if eval "test x$CURSES_LIB_NAME = x"; then
		AC_CHECK_LIB(curses, initscr, [CURSES_LIB="-lcurses" CURSES_LIB_NAME=curses])
	fi
fi

if eval "test x$CURSES_LIB_NAME = x"; then
	AC_MSG_ERROR([
  *** No curses lib was found.  Please install the curses header files
  *** from libncurses-dev (Debian), ncurses-devel (Fedora), or similar.
  *** (Or install ncurses from https://ftp.gnu.org/gnu/ncurses/.)])
else
	AC_MSG_RESULT([  The curses library to be used is: $CURSES_LIB_NAME])
fi

AC_CHECK_LIB([$CURSES_LIB_NAME], [use_default_colors],
			 [AC_DEFINE(HAVE_USE_DEFAULT_COLORS, 1, [Define this if your curses library has the use_default_colors() function.])],
			 [], [$CURSES_LIB])
AC_CHECK_LIB([$CURSES_LIB_NAME], [set_escdelay],
			 [AC_DEFINE(HAVE_SET_ESCDELAY, 1, [Define this if your curses library has the set_escdelay() function.])],
			 [], [$CURSES_LIB])
AC_CHECK_LIB([$CURSES_LIB_NAME], [key_defined],
			 [AC_DEFINE(HAVE_KEY_DEFINED, 1, [Define this if your curses library has the key_defined() function.])],
			 [], [$CURSES_LIB])

LIBS="$LIBS $CURSES_LIB"

AC_SUBST(CURSES_LIB)

if test "x$enable_utf8" != xno && \
	test x$CURSES_LIB_WIDE = xyes && \
	test x$ac_cv_func_iswalpha = xyes && \
	test x$ac_cv_func_iswalnum = xyes && \
	test x$ac_cv_func_iswpunct = xyes && \
	test x$ac_cv_func_mbstowcs = xyes && \
	test x$ac_cv_func_wctomb = xyes; then
		AC_DEFINE(ENABLE_UTF8, 1, [Define this if your system has sufficient UTF-8 support.])
else
	if test "x$enable_utf8" = xyes; then
		AC_MSG_ERROR([
  *** UTF-8 support was requested, but insufficient support was
  *** detected in your curses and/or C libraries.  Please verify
  *** that both your curses library and your C library were built
  *** with wide-character support.])
	elif test "x$enable_utf8" != xno; then
		AC_MSG_WARN([
  *** Insufficient UTF-8 support was detected in your curses
  *** and/or C libraries.  If you want UTF-8 support, please
  *** verify that both your curses library and your C library
  *** were built with wide-character support.])
	fi
fi

AC_CACHE_CHECK([for enhanced regular expression flag], nano_cv_flag_reg_enhanced,
			   [AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <regex.h>]],
												   [[
													 #ifndef REG_ENHANCED
													 error: No REG_ENHANCED support!
													 #endif
												   ]])],
								  [nano_cv_flag_reg_enhanced=yes],
								  [nano_cv_flag_reg_enhanced=no])])
dnl The bundled gnulib regex module doesn't support REG_ENHANCED.
if test "$ac_use_included_regex" = "yes"; then
	nano_cv_flag_reg_enhanced="no"
fi
if test "$nano_cv_flag_reg_enhanced" = "yes"; then
	nano_reg_extended="REG_EXTENDED | REG_ENHANCED"
else
	nano_reg_extended="REG_EXTENDED"
fi

AC_DEFINE_UNQUOTED(NANO_REG_EXTENDED, $nano_reg_extended,
				   [Flag(s) to use to get the full range of extended regular expressions])

if test x$color_support = xyes; then
	AC_MSG_CHECKING([whether _XOPEN_SOURCE_EXTENDED is needed])
	AC_RUN_IFELSE([AC_LANG_SOURCE([[
#include <curses.h>
int main(void)
{
	int testcolor = COLOR_WHITE;
	return 0;
}]])],
	AC_MSG_RESULT(no),
	AC_RUN_IFELSE([AC_LANG_SOURCE([[
#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED 1
#endif
#include <curses.h>
int main(void)
{
	int testcolor = COLOR_WHITE;
	return 0;
}]])],
	AC_DEFINE(NEED_XOPEN_SOURCE_EXTENDED, 1, [Define this if you need the _XOPEN_SOURCE_EXTENDED macro for color support.])
	AC_MSG_RESULT(yes),
	AC_MSG_RESULT(not sure)
	AC_MSG_WARN([
  *** Couldn't successfully compile basic color test with or without
  *** _XOPEN_SOURCE_EXTENDED.  This build may not compile.  Consider
  *** configuring with --disable-color or installing ncurses.])),
	AC_MSG_WARN([
  *** Can't check need for _XOPEN_SOURCE_EXTENDED when cross-compiling.]))
fi

AS_IF([test "x$enable_libmagic" != "xno"], [
	AC_CHECK_HEADERS([magic.h])
	AC_CHECK_LIB(magic, magic_open)
	AC_CHECK_HEADERS([zlib.h])
	AC_CHECK_LIB(z, inflate)
])

# Check for groff html support.
AC_MSG_CHECKING([for HTML support in groff])
groff -t -mandoc -Thtml </dev/null >/dev/null
if test $? -ne 0 ; then
	AC_MSG_RESULT([no])
	AC_MSG_WARN([
  *** Will not generate HTML version of man pages.  Consider
  *** installing a newer version of groff with HTML support.])
	groff_html_support=no
else
	AC_MSG_RESULT([yes])
	groff_html_support=yes
fi
AM_CONDITIONAL(GROFF_HTML, test x$groff_html_support = xyes)

AC_CONFIG_FILES([
Makefile
doc/Makefile
doc/sample.nanorc
lib/Makefile
m4/Makefile
po/Makefile.in
src/Makefile
syntax/Makefile
])

AC_OUTPUT

make showinfo
