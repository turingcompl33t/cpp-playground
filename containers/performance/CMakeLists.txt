# containers/performance/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(container-perf CXX)

include("../../_CMake/benchmark.cmake")
include("../../_CMake/warnings.cmake")
include("../../_CMake/threads.cmake")

add_subdirectory("../../_Deps/benchmark" ${CMAKE_CURRENT_BINARY_DIR}/benchmark)

add_executable(vector_vs_deque "vector_vs_deque.cpp")
target_link_libraries(vector_vs_deque PRIVATE benchmark warnings threads)

add_executable(hashtable_index "hashtable_index.cpp")
target_link_libraries(hashtable_index PRIVATE benchmark warnings threads)