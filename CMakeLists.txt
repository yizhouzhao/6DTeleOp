cmake_minimum_required(VERSION 3.10)

# Project name
project(6DTeleop)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Find all .cpp and .h files under src/
file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/*.h
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# (Optional) If you have additional include directories, you can add:
# target_include_directories(${PROJECT_NAME} PRIVATE include)
