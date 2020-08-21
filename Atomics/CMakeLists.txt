# Atomics/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(atomics CXX)

add_subdirectory("../_Deps/catch2" ${CMAKE_CURRENT_BINARY_DIR}/catch2)

add_executable(lockfree_shared_ptr "lockfree_shared_ptr.cpp")

add_executable(sequentially_consistent "sequentially_consistent.cpp")
target_link_libraries(sequentially_consistent Catch2 pthread)