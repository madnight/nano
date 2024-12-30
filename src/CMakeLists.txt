# Define the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Define the project name and version
project(nano VERSION 8.3)

# Define the source files for the nano executable
set(SRC_FILES
    browser.c
    chars.c
    color.c
    cut.c
    files.c
    global.c
    help.c
    history.c
    move.c
    nano.c
    prompt.c
    rcfile.c
    search.c
    text.c
    utils.c
    winio.c
)

# Add the executable target named nano
add_executable(nano ${SRC_FILES})

# Link necessary libraries and include directories
target_link_libraries(nano PRIVATE libgnu)
target_include_directories(nano PRIVATE ${CMAKE_SOURCE_DIR}/lib)

# Set required compiler flags and options
target_compile_options(nano PRIVATE -Wall -Wextra -Werror)
