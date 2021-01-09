# utilities/variant/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(variant CXX)

include("../../_CMake/warnings.cmake")

add_subdirectory("../../_Deps/catch2" ${CMAKE_CURRENT_BINARY_DIR}/catch2)

add_executable(variant1 "variant1.cpp")
target_link_libraries(variant1 warnings Catch2)

add_executable(variant2 "variant2.cpp")
target_link_libraries(variant2 warnings Catch2)