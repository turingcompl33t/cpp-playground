# Atomics/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(atomics CXX)

include("../../_CMake/benchmark.cmake")
include("../../_CMake/warnings.cmake")
include("../../_CMake/threads.cmake")

add_subdirectory("../../_Deps/benchmark" ${CMAKE_CURRENT_BINARY_DIR}/benchmark)

add_executable(bench_atomic_vs_mutex "bench_atomic_vs_mutex.cpp")
target_link_libraries(bench_atomic_vs_mutex PRIVATE benchmark threads warnings)

add_executable(bench_sharing "bench_sharing.cpp")
target_link_libraries(bench_sharing PRIVATE benchmark threads warnings)