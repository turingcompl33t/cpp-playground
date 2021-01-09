# span/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(span CXX)

include("../_CMake/warnings.cmake")

add_subdirectory("../_Deps/catch2" ${CMAKE_CURRENT_BINARY_DIR}/catch2)

add_executable(span "span.cpp")
target_link_libraries(span warnings Catch2)