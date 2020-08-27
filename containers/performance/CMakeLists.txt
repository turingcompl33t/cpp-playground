# containers/performance/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(container-perf CXX)

include("../../_CMake/benchmark.cmake")
include("../../_CMake/warnings.cmake")
include("../../_CMake/threads.cmake")

add_subdirectory("../../_Deps/benchmark" ${CMAKE_CURRENT_BINARY_DIR}/benchmark)

add_executable(bench_vector_deque "bench_vector_deque.cpp")
target_link_libraries(bench_vector_deque PRIVATE benchmark warnings threads)

add_executable(bench_hashtable_index "bench_hashtable_index.cpp")
target_link_libraries(bench_hashtable_index PRIVATE benchmark warnings threads)

add_executable(bench_lookup "bench_lookup.cpp")
target_link_libraries(bench_lookup PRIVATE benchmark warnings threads)