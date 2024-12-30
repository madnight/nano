# Define the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Define the source files for the libgnu library
set(LIBGNU_SRC_FILES
    canonicalize.c
    futimens.c
    getdelim.c
    getline.c
    getopt.c
    glob.c
    isblank.c
    iswblank.c
    lstat.c
    mkstemps.c
    nl_langinfo.c
    regex.c
    sigaction.c
    snprintf.c
    stdarg.c
    strcase.c
    strcasestr.c
    strnlen.c
    sys_wait.c
    vsnprintf.c
    wchar.c
    wctype.c
    wcwidth.c
)

# Add a static library target named libgnu
add_library(libgnu STATIC ${LIBGNU_SRC_FILES})

# Set required compiler flags and options
target_compile_options(libgnu PRIVATE -Wall -Wextra -Werror)
