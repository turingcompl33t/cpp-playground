# advent2020/day15/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(advent2020-day15 CXX)

include("../../../_CMake/warnings.cmake")

add_executable(puzzle1 "puzzle1.cpp")
target_link_libraries(puzzle1 warnings)

add_executable(puzzle2 "puzzle2.cpp")
target_link_libraries(puzzle2 warnings)