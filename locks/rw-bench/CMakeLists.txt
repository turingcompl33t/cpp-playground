# locks/rw-bench/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(rw-bench CXX)

include("../../_CMake/warnings.cmake") 
include("../../_CMake/threads.cmake")

# ensure that FindTBB.cmake functionality is available
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

# assumes a global installation of TBB
find_package(TBB REQUIRED)
message(STATUS "[FOUND] TBB ${TBB_VERSION}")

add_subdirectory("../../_Deps/catch2" ${CMAKE_CURRENT_BINARY_DIR}/catch2)

add_executable(bench_latency "bench_latency.cpp")
target_link_libraries(bench_latency PRIVATE warnings threads ${TBB_LIBRARIES_RELEASE})
target_include_directories(bench_latency PRIVATE ${TBB_INCLUDE_DIR})

add_executable(bench_throughput "bench_throughput.cpp")
target_link_libraries(bench_throughput PRIVATE warnings threads ${TBB_LIBRARIES_RELEASE})
target_include_directories(bench_throughput PRIVATE ${TBB_INCLUDE_DIR})