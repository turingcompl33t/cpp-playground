# locks/spinlock/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(spinlock CXX)

include("../../_CMake/warnings.cmake") 
include("../../_CMake/threads.cmake")

add_subdirectory("../../_Deps/catch2" ${CMAKE_CURRENT_BINARY_DIR}/catch2)

add_executable(test "test.cpp")
target_link_libraries(test PRIVATE Catch2 warnings threads)

add_executable(bench "bench.cpp")
target_link_libraries(bench PRIVATE warnings threads)