// sort.cpp
//
// Demo of std:sort()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 sort.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <random>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

TEST_CASE("std::sort()")
{
    auto c = std::vector<int>(10);
    std::iota(c.begin(), c.end(), 0);  // 0 - 9

    std::mt19937 g(std::random_device{}());

    std::shuffle(c.begin(), c.end(), g);

    std::sort(c.begin(), c.end());

    REQUIRE(c.front() == 0);
    REQUIRE(c.back() == 9);

    REQUIRE(std::is_sorted(c.begin(), c.end()));
}