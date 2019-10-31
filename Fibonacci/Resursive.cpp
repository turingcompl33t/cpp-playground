// Recursive.cpp
// The absolute simplest implementation of Fibonacci sequence via recursion.

#include <iostream>

// making this constexpr does not improve performance much
int fib(int n)
{
    if (0 == n) return 0;
    if (1 == n) return 1;
    return fib(n - 1) + fib(n - 2); 
}

int main()
{
    std::cout << fib(10) << '\n';
}