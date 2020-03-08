// folds.cpp
// Demo of basic variadic template fold expressions.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 folds.cpp

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// sum with left associative fold
template <typename... Ts>
auto sum_left(Ts... ts)
{
    // ((pack1 op pack2) op pack3) ...
    return ( ... + ts );
}

// sum with right associative fold
template <typename... Ts>
auto sum_right(Ts... ts)
{
    // ... (packN-2 op (packN-1 op PackN))
    return ( ts + ... );
}

// sum with left associative fold and initializer
template <typename Init, typename... Ts>
auto sum_left_init(Init init, Ts... ts)
{
    // ((init op pack1) op pack2) ...
    return ( init + ... + ts );
}

// sum with right associative fold and initializer
template <typename Init, typename... Ts>
auto sum_right_init(Init init, Ts... ts)
{
    // ... (packN-1 (packN op init))
    return ( ts + ... + init);
}

TEST_CASE("sum function template computes the expected value when")
{
    SECTION("left associative fold is performed")
    {
        auto r = ::sum_left(1, 2, 3, 4);
        REQUIRE(r == 10);
    }

    SECTION("right associative fold is performed")
    {
        auto r = ::sum_right(1, 2, 3, 4);
        REQUIRE(r == 10);
    }

    SECTION("left associative fold with initializer is performed")
    {
        auto r = ::sum_left_init(0, 1, 2, 3, 4);
        REQUIRE(r == 10);
    }

    SECTION("right associative fold with initializer is performed")
    {
        auto r = ::sum_right_init(0, 1, 2, 3, 4);
        REQUIRE(r == 10);
    }
}