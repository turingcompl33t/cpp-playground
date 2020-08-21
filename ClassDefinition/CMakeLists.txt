# ClassDefinition/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(class-definition CXX)

add_subdirectory("../_Deps/catch2" ${CMAKE_CURRENT_BINARY_DIR}/catch2)

add_executable(ref_qualified "ref_qualified.cpp")
target_link_libraries(ref_qualified PRIVATE Catch2)