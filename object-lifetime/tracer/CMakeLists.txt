# object-lifetime/tracer/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(lifetime-tracer CXX)

include("../../_CMake/warnings.cmake")

add_executable(tracer "tracer.cpp")
target_link_libraries(tracer PRIVATE warnings)