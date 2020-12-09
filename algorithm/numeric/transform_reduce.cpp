// transform_reduce.cpp
// Usage of std::transform_reduce()

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <numeric>
#include <algorithm>

TEST_CASE("std::transform_reduce() is the greatest algorithm ever")
{
    auto c = std::vector<int>(10);
    std::iota(c.begin(), c.end(), 0);

    // computes sum of squares from 0 - 9
    auto res = std::transform_reduce(
        c.begin(), 
        c.end(), 
        0,
        std::plus{},
        [](auto a){ return a*a; });

    REQUIRE(res == 285);
}