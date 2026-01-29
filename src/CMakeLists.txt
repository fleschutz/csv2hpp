# Cross-platform CMake Build Instructions for csv2hpp
# ===================================================

cmake_minimum_required(VERSION 3.10)

project(examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(.)

add_executable(csv2hpp csv2hpp.cpp)

# add unit tests
enable_testing()
add_test(NAME csv2hpp COMMAND csv2hpp --help)

install(TARGETS csv2hpp DESTINATION . )

