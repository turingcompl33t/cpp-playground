# Atomics/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(atomics CXX)

include("../_CMake/warnings.cmake")
include("../_CMake/threads.cmake")

add_subdirectory("../_Deps/benchmark" ${CMAKE_CURRENT_BINARY_DIR}/benchmark)
add_subdirectory("../_Deps/catch2" ${CMAKE_CURRENT_BINARY_DIR}/catch2)

add_executable(lockfree_shared_ptr "lockfree_shared_ptr.cpp")
target_link_libraries(lockfree_shared_ptr PRIVATE warnings)

add_executable(sequentially_consistent "sequentially_consistent.cpp")
target_link_libraries(sequentially_consistent PRIVATE Catch2 threads warnings)