# Benchmarking/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(benchmarking CXX)

include("../_CMake/benchmark.cmake")
include("../_CMake/warnings.cmake")
include("../_CMake/threads.cmake")

add_subdirectory("../_Deps/benchmark" ${CMAKE_CURRENT_BINARY_DIR}/benchmark)

add_executable(sample "sample.cpp")
target_link_libraries(sample PRIVATE benchmark warnings threads)