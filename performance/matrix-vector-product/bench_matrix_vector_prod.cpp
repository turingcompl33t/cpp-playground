// bench_matrix_vector_prod.cpp

#include <benchmark/benchmark.h>

#include <cstdlib>

#include "matrix_vector_prod_naive.hpp"
#include "matrix_vector_prod_vectorized.hpp"

constexpr static std::size_t const REQUIRED_ALIGNMENT = 32;

static float* allocate(std::size_t n)
{
    auto const ptr = ::malloc(sizeof(float)*n);
    if (nullptr == ptr)
    {
        std::terminate();
    }

    return static_cast<float*>(ptr);
}

static float* allocate_aligned(std::size_t n)
{
    void* ptr{};
    auto const res = ::posix_memalign(&ptr, REQUIRED_ALIGNMENT, sizeof(float)*n);
    if (res != 0)
    {
        std::terminate();
    }

    return static_cast<float*>(ptr);
}

static void fill_random(std::size_t n, float*& a, unsigned int seed)
{
    ::srand(seed);
    unsigned int s1 = seed;
    unsigned int s2 = seed;
    for (std::size_t i = 0; i < n; ++i)
    {
        a[i] = static_cast<float>(rand_r(&s1)*rand_r(&s2));
    }
}

void BM_mv_product_naive(benchmark::State& state)
{
    auto const n = static_cast<std::size_t>(state.range(0));

    float* matrix = allocate(n*n);
    float* vector = allocate(n);
    float* result = allocate(n);

    fill_random(n*n, matrix, 1);
    fill_random(n, vector, 1);

    for (auto _ : state)
    {
        mv_product_naive(n, matrix, vector, result);
    }

    ::free(matrix);
    ::free(vector);
    ::free(result);

    // NOTE: why does the benchmark API accept counts of items
    // processed and bytes processed as a signed value..?
    state.SetItemsProcessed(
        static_cast<int64_t>(n*n*state.iterations()));
    state.SetBytesProcessed(
        static_cast<int64_t>(sizeof(float)*n*(n+2)*state.iterations()));

    char buffer[256];
    ::snprintf(buffer, sizeof(buffer), "Memory: %g+%g+%g (K)", 
        static_cast<double>(sizeof(float)*n*n)/1024.0, 
        static_cast<double>(sizeof(float)*n)/1024.0, 
        static_cast<double>(sizeof(float)*n)/1024.0);

    state.SetLabel(buffer);
}

void BM_mv_product_vectorized(benchmark::State& state)
{
    auto const n = static_cast<std::size_t>(state.range(0));

    float* matrix = allocate_aligned(n*n);
    float* vector = allocate_aligned(n);
    float* result = allocate_aligned(n);

    fill_random(n*n, matrix, 1);
    fill_random(n, vector, 1);

    for (auto _ : state)
    {
        mv_product_vectorized(n, matrix, vector, result);
    }

    ::free(matrix);
    ::free(vector);
    ::free(result);

    // NOTE: why does the benchmark API accept counts of items
    // processed and bytes processed as a signed value..?
    state.SetItemsProcessed(
        static_cast<int64_t>(n*n*state.iterations()));
    state.SetBytesProcessed(
        static_cast<int64_t>(sizeof(float)*n*(n+2)*state.iterations()));

    char buffer[256];
    ::snprintf(buffer, sizeof(buffer), "Memory: %g+%g+%g (K)", 
        static_cast<double>(sizeof(float)*n*n)/1024.0, 
        static_cast<double>(sizeof(float)*n)/1024.0, 
        static_cast<double>(sizeof(float)*n)/1024.0);

    state.SetLabel(buffer);
}

BENCHMARK(BM_mv_product_naive)->RangeMultiplier(2)->Range(1 << 8, 1 << 10);
BENCHMARK(BM_mv_product_vectorized)->RangeMultiplier(2)->Range(1 << 8, 1 << 10);

BENCHMARK_MAIN();