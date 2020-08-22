// accumulate.cpp
//
// Demo of std::accumulate()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 accumulate.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <algorithm>
#include <numeric>

TEST_CASE("std::accumulate()")
{
    auto c = std::vector<int>(100);
    std::iota(c.begin(), c.end(), 0);  // 0 - 99

    auto sum = std::accumulate(c.begin(), c.end(), 0);
    REQUIRE(sum == 4950);
}