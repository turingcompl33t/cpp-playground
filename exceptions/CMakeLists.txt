# benchmarking/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(exceptions CXX)

include("../_CMake/warnings.cmake")

add_subdirectory("../_Deps/catch2" ${CMAKE_CURRENT_BINARY_DIR}/catch2)

add_executable(basics "basics.cpp")
target_link_libraries(basics PRIVATE Catch2 warnings)

add_executable(guarantees "guarantees.cpp")
target_link_libraries(guarantees PRIVATE Catch2 warnings)