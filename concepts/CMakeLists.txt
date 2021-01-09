# concepts/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(concepts CXX)

include("../_CMake/warnings.cmake")

add_subdirectory("../_Deps/catch2" ${CMAKE_CURRENT_BINARY_DIR}/catch2)

add_executable(hello "hello.cpp")
target_link_libraries(hello warnings Catch2)

add_executable(overload "overload.cpp")
target_link_libraries(overload warnings Catch2)

add_executable(require1 "require1.cpp")
target_link_libraries(require1 warnings Catch2)