# concurrency/threadpool/basic/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(thread-pool-local CXX)

include("../../../_CMake/benchmark.cmake")
include("../../../_CMake/warnings.cmake")
include("../../../_CMake/threads.cmake")

add_subdirectory("../../../_Deps/benchmark" ${CMAKE_CURRENT_BINARY_DIR}/benchmark)
add_subdirectory("../../../_Deps/catch2" ${CMAKE_CURRENT_BINARY_DIR}/catch2)
add_subdirectory("../../../_Deps/cdl" ${CMAKE_CURRENT_BINARY_DIR}/cdl)

add_executable(test "test.cpp")
target_link_libraries(test PRIVATE warnings threads Catch2 cdl)
target_compile_features(test PRIVATE cxx_std_20)

add_executable(bench "bench.cpp")
target_link_libraries(bench PRIVATE warnings threads benchmark cdl)
target_compile_features(test PRIVATE cxx_std_20)