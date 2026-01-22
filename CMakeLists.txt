# Cross-platform CMake Build Instructions for csv2hpp
# ===================================================

cmake_minimum_required(VERSION 3.10)

project(examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(.)

add_executable(csv2hpp main.cpp)

install(TARGETS csv2hpp DESTINATION . )

