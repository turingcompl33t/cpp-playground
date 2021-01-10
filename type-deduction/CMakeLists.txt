# type-deduction/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(type-deduction CXX)

include("../_CMake/warnings.cmake")

add_subdirectory("../_Deps/catch2" ${CMAKE_CURRENT_BINARY_DIR}/catch2)

add_executable(decltype1 "decltype1.cpp")
target_link_libraries(decltype1 warnings Catch2)

add_executable(decltype2 "decltype2.cpp")
target_link_libraries(decltype2 warnings Catch2)