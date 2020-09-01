# object-orientation/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(object-orientation CXX)

add_subdirectory("../_Deps/catch2" ${CMAKE_CURRENT_BINARY_DIR}/catch2)

add_executable(ref_qualified "ref_qualified.cpp")
target_link_libraries(ref_qualified PRIVATE Catch2)

add_executable(inheritance "inheritance.cpp")
target_link_libraries(inheritance PRIVATE Catch2)