# ranges/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(ranges CXX)

include("../_CMake/benchmark.cmake")
include("../_CMake/warnings.cmake")
include("../_CMake/threads.cmake")

add_subdirectory("../_Deps/catch2" ${CMAKE_CURRENT_BINARY_DIR}/catch2)
add_subdirectory("../_Deps/rangev3" ${CMAKE_CURRENT_BINARY_DIR}/rangev3)

add_executable(it_works "it_works.cpp")
target_link_libraries(it_works warnings threads Catch2 range-v3)