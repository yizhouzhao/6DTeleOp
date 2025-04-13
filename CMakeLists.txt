cmake_minimum_required(VERSION 3.10)

# Project name
project(6DTeleop)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable building the Imath library from the submodule
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries" FORCE)
set(IMATH_INSTALL_PKG_CONFIG OFF CACHE BOOL "Install pkg-config files" FORCE)
set(IMATH_INSTALL_SYM_LINK OFF CACHE BOOL "Create symlinks for Imath includes" FORCE)

# Add Imath as a subdirectory
add_subdirectory(extern/Imath)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Add our source directory
add_subdirectory(src)