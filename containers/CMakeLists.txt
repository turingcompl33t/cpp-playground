# containers/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(containers CXX)

include("../_CMake/warnings.cmake")

add_subdirectory("../_Deps/catch2" ${CMAKE_CURRENT_BINARY_DIR}/catch2)

add_executable(heap "heap.cpp")
target_link_libraries(heap PRIVATE warnings Catch2)

add_executable(list "list.cpp")
target_link_libraries(list PRIVATE warnings Catch2)