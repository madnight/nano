cmake_minimum_required(VERSION 3.10)

project(nano VERSION 8.3)

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(doc)
add_subdirectory(po)
add_subdirectory(syntax)

# Include necessary CMake modules and set required CMake policies
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
