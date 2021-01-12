# utilities/optional/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(allocators CXX)

include("../../_CMake/warnings.cmake")

add_subdirectory("../../_Deps/catch2" ${CMAKE_CURRENT_BINARY_DIR}/catch2)

add_executable(optional1 "optional1.cpp")
target_link_libraries(optional1 warnings Catch2)