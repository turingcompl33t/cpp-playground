// matrix_vector_prod_vectorized.hpp
//
// Vectorized implementation of matrix-vector product.
//
// Inspired by Fedor Pikus' CppCon 2018 talk:
// "Design for Performance"

#ifndef MATRIX_VECTOR_PROD_VECTORIZED_HPP
#define MATRIX_VECTOR_PROD_VECTORIZED_HPP

#include <immintrin.h>

float prod8(float const* a, float const* b)
{
    union
    {
        float r[8];
        __m256 rv;
    };

    // _mm256_load_ps
    // moves packed, single-precision floating point values from an 
    // aligned memory location to a destination vector, returning 
    // the destination vector that results from the operation

    // _mm_dp_ps
    // calculates the dot product of single-precision packed values
    // the final argument is a mask that describes the parts of the
    // result that are summed versus those that are zeroed

    rv = _mm256_dp_ps(_mm256_load_ps(a), _mm256_load_ps(b), 0xF1);
    return r[0] + r[4];
}

float vv_product(std::size_t n, float const* a, float const* b)
{
    float res = 0;
    for (std::size_t i = 0; i < n; i += 8)
    {
        res += prod8(a + i, b + i);
    }

    return res;
}

// assumes that 
void mv_product_vectorized(
    std::size_t  n, 
    float const* matrix, 
    float const* vector, 
    float*       result)
{
    float const* tmp = matrix;
    for (std::size_t i = 0; i < n; ++i)
    {
        result[i] = vv_product(n, tmp, vector);
        tmp += n;
    }
}

#endif // MATRIX_VECTOR_PROD_VECTORIZED_HPP