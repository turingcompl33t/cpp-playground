// is_prime2.cpp
// Compile time computation with C++11 features.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++17 /I C:\Dev\Catch2 is_prime2.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

constexpr bool is_prime_impl(unsigned p, unsigned d)
{
    return d != 2
        ? (p%d != 0) && is_prime_impl(p, d-1)
        : (p%2 != 0);
}

constexpr bool is_prime(unsigned p)
{
    return p < 4
        ? !(p < 2)
        : is_prime_impl(p, p/2);
}

TEST_CASE("is_prime computes primality at compile time")
{
    REQUIRE(is_prime(7));
    REQUIRE_FALSE(is_prime(9));
}