// Template.cpp
// Compute the Fibonacci sequence at compile-time using template metaprogramming.

#include <array>
#include <utility>
#include <iostream>

template<int I>
struct Fib
{
    static const int val = Fib<I-1>::val + Fib<I-2>::val;
};

template<>
struct Fib<0>
{
    static const int val = 0;
};

template<>
struct Fib<1>
{
    static const int val = 1;
};

// std::integer_sequence<0, 1, 2, ... 46>

template<size_t ... I>
int fib_impl(std::index_sequence<I...>, const int n)
{
    constexpr std::array<int, sizeof...(I)> a = { Fib<I>::val... };
    return a[n];
}

const int fib(const int n)
{
    return fib_impl(std::make_index_sequence<47>(), n);
}

int main()
{
    std::cout << fib(10) << '\n';
}