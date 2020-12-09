# algorithm/numeric/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(numeric CXX)

include("../../_CMake/warnings.cmake")

add_subdirectory("../../_Deps/catch2" ${CMAKE_CURRENT_BINARY_DIR}/catch2)

add_executable(accumulate "accumulate.cpp")
target_link_libraries(accumulate PRIVATE Catch2)

add_executable(iota "iota.cpp")
target_link_libraries(iota PRIVATE Catch2)

add_executable(reduce "reduce.cpp")
target_link_libraries(reduce PRIVATE Catch2)

add_executable(transform-reduce "transform_reduce.cpp")
target_link_libraries(transform-reduce PRIVATE Catch2)