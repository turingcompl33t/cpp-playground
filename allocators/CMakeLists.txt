# allocators/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(allocators CXX)

include("../_CMake/benchmark.cmake")
include("../_CMake/warnings.cmake")
include("../_CMake/threads.cmake")

add_subdirectory("../_Deps/benchmark" ${CMAKE_CURRENT_BINARY_DIR}/benchmark)
add_subdirectory("../_Deps/catch2" ${CMAKE_CURRENT_BINARY_DIR}/catch2)

add_executable(null "null.cpp")
target_link_libraries(null warnings threads Catch2)

add_executable(monotonic_buffer "monotonic_buffer.cpp")
target_link_libraries(monotonic_buffer warnings)

add_executable(bench_list_allocators "bench_list_allocators.cpp")
target_link_libraries(bench_list_allocators warnings threads benchmark)