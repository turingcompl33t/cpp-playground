// matrix_vector_prod_naive.hpp
//
// Naive implementation of matrix-vector product.
//
// Inspired by Fedor Pikus' CppCon 2018 talk:
// "Design for Performance"

#ifndef MATRIX_VECTOR_PROD_NAIVE_HPP
#define MATRIX_VECTOR_PROD_NAIVE_HPP

#include <cstdint>

void mv_product_naive(
    std::size_t  n, 
    float const* matrix, 
    float const* vector, 
    float*       result)
{
    float const* tmp = matrix;
    for (std::size_t i = 0; i < n; ++i)
    {
        float& accumulator = result[i];
        
        accumulator = 0;
        for (std::size_t j = 0; j < n; ++j)
        {
            accumulator += tmp[j]*vector[j];
        }

        tmp += n;
    }
}

#endif // MATRIX_VECTOR_PROD_NAIVE_HPP