# misc/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(benchmarking CXX)

include("../_CMake/warnings.cmake")
include("../_CMake/threads.cmake")

add_executable(thread_local "thread_local.cpp")
target_link_libraries(thread_local PRIVATE warnings threads)