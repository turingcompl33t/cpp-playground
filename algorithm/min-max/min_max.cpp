// min_max.cpp
//
// Demo of STL minimum / maximum algorithms
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 min_max.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <numeric>
#include <algorithm>

TEST_CASE("std::min()")
{
    REQUIRE(std::min(5, 10) == 5);
}

TEST_CASE("std::max()")
{
    REQUIRE(std::max(5, 10) == 10);
}

TEST_CASE("std::min_element()")
{
    auto c = std::vector<int>(10);
    std::iota(c.begin(), c.end(), 0);

    auto min = std::min_element(c.begin(), c.end());

    REQUIRE(*min == 0);
}

TEST_CASE("std::max_element()")
{
    auto c = std::vector<int>(10);
    std::iota(c.begin(), c.end(), 0);

    auto max = std::max_element(c.begin(), c.end());

    REQUIRE(*max == 9);
}

TEST_CASE("std::minmax_element()")
{
    auto c = std::vector<int>(10);
    std::iota(c.begin(), c.end(), 0);

    auto minmax = std::minmax_element(c.begin(), c.end());

    REQUIRE(*minmax.first == 0);
    REQUIRE(*minmax.second == 9);
}