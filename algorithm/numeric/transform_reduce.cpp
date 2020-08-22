// transform_reduce.cpp
//
// Demo of std::transform_reduce()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 transform_reduce.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

TEST_CASE("std::transform_reduce()")
{
    auto c = std::vector<int>(10);
    std::iota(c.begin(), c.end(), 0);

    auto add    = [](auto a, auto b){ return a + b; };
    auto square = [](auto a){ return a*a; };

    // transform by squaring all elements
    // reduce via accumulation (sum)

    // computes sum of squares from 0 - 9
    auto res = std::transform_reduce(
        c.begin(), 
        c.end(), 
        0,
        add,
        square
        );

    REQUIRE(res == 285);
}