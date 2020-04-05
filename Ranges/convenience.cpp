// convenience.cpp
// Demo of basic range utility: convenience.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++latest /permissive- /experimental:preprocessor /I %CPP_WORKSPACE%\_Deps\Catch2 /I %CPP_WORKSPACE%\_Deps\RangeV3\Include convenience.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <range/v3/all.hpp>

TEST_CASE("ranges provide convenience over STL iterator abstraction")
{
    auto v1 = std::vector<int>{3, 2, 1};
    std::sort(v1.begin(), v1.end());

    REQUIRE(std::is_sorted(v1.begin(), v1.end()));

    auto v2 = std::vector<int>{3, 2, 1};
    ranges::sort(v2);

    REQUIRE(ranges::is_sorted(v2));
}