// Variadic.cpp
// Simple variadic lambda.

#include <iostream>

template <typename T, typename... Ts>
T sum(T x, Ts... xs)
{
    return x + sum(xs...);
}

template <typename T>
T sum(T x)
{
    return x;
}

int main()
{   
    auto f = [](auto... xs) {
        return sum(xs...);
    };

    auto r1 = sum(1, 2, 3, 4, 5);

    auto r2 = f(1, 2, 3, 4, 5);

    std::cout << "Using variadic template: " << r1 << std::endl;
    std::cout << "Using variadic lambda:   " << r2 << std::endl;
}