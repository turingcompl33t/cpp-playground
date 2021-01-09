# object-model/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(object-model CXX)

include("../_CMake/warnings.cmake")

add_subdirectory("../_Deps/catch2" ${CMAKE_CURRENT_BINARY_DIR}/catch2)

add_executable(ref_qualified "ref_qualified.cpp")
target_link_libraries(ref_qualified PRIVATE Catch2)

add_executable(poly1 "poly1.cpp")
target_link_libraries(poly1 warnings Catch2)

add_executable(poly2 "poly2.cpp")
target_link_libraries(poly2 warnings Catch2)

add_executable(forwarding1 "forwarding1.cpp")
target_link_libraries(forwarding1 warnings Catch2)