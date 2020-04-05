// fibonacci.cpp
// Compile-time computation of Nth Fibonacci number via TMP.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++17 /I %CPP_WORKSPACE%\_Deps\Catch2 fibonacci.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

template<int N>
struct fibonacci
{
    static int const value { fibonacci<N - 1>::value + fibonacci<N - 2>::value };
};

template <>
struct fibonacci<1> { static int const value { 1 }; };
template <>
struct fibonacci<0> { static int const value { 1 }; };

TEST_CASE("nth value in fibonacci sequence is computed at compile time")
{
    // assumes the sequence is zero indexed:
    // i.e. Fib(0) = 1, Fib(1) = 1, Fib(2) = 2, etc...
    // thus, '9' here denotes:
    // - compute the value at index 9 in the sequence 
    // - OR, equivalently, compute the 10th value in the sequence

    REQUIRE(fibonacci<9>::value == 55);
}