// Fibonacci.cpp
// Compile-time computation of Nth Fibonacci number via TMP.

#include <iostream>

template<int N>
struct Fibonacci
{
    static int const Value { Fibonacci<N - 1>::Value + Fibonacci<N - 2>::Value };
};

template<>
struct Fibonacci<1>
{
    static int const Value { 1 };
};

template<>
struct Fibonacci<0>
{
    static int const Value { 1 };
};

int main()
{
    // assumes the sequence is zero indexed:
    // i.e. Fib(0) = 1, Fib(1) = 1, Fib(2) = 2, etc...
    // thus, '9' here denotes:
    // - compute the value at index 9 in the sequence 
    // - OR, equivalently, compute the 10th value in the sequence
    
    std::cout << Fibonacci<9>::Value << std::endl;
}