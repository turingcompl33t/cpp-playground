# Performance/CMakeLists.txt

cmake_minimum_required(VERSION 3.17)

project(performance CXX)

include("../_CMake/benchmark.cmake")
include("../_CMake/warnings.cmake")
include("../_CMake/threads.cmake")

add_subdirectory("../_Deps/benchmark" ${CMAKE_CURRENT_BINARY_DIR}/benchmark)

add_executable(bench_matrix_vector_prod "bench_matrix_vector_prod.cpp")
target_link_libraries(bench_matrix_vector_prod PRIVATE benchmark warnings threads)

# for obvious reasons, the optimization level makes a HUGE difference
# when running this benchmark; for instance between -O0 (no optimization)
# and -O3 I see a ~4x increase in the number of bytes processed per second
# and from there, moving from -O3 to -Ofast, I see a further ~2x increase
# in the bytes per second throughput, likely because -Ofast enables -ffast-math
target_compile_options(bench_matrix_vector_prod PRIVATE "-Ofast" "-mavx2")