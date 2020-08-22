// is_prime3.cpp
// Compile time computation with C++14 features.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++17 /I %CPP_WORKSPACE%\_Deps\Catch2 is_prime3.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

constexpr bool is_prime(unsigned p)
{
    for (unsigned int d = 2; d <= p/2; ++d)
    {
        if (p%d == 0) return false;
    }
    return p > 1;
}

TEST_CASE("is_prime computes primality at compile time")
{
    REQUIRE(is_prime(7));
    REQUIRE_FALSE(is_prime(9));
}