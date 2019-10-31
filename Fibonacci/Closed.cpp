// Closed.cpp
// Closed-form implementation of Fibonacci sequence.

#include <cmath>
#include <iostream>

constexpr int fib(int n)
{
    // this won't compile under MSVC, but both clang and GCC recognize this as valid constexpr
    constexpr auto sqrt_5 = std::sqrt(5);

    if (0 == n) return 0;
    if (1 == n) return 1;
    return static_cast<int>((std::pow(1 + sqrt_5, n) - std::pow(1 - sqrt_5, n)) / (std::pow(2, n) * sqrt_5));
}

int main()
{
    std::cout << fib(10) << '\n';
}