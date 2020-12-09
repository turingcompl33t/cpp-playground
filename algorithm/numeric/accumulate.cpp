// accumulate.cpp
// Usage of std::accumulate()

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <algorithm>
#include <numeric>

TEST_CASE("std::accumulate defaults to using std::plus as the accumulator")
{
    auto c = std::vector<int>(100);
    std::iota(c.begin(), c.end(), 0);

    const auto sum = std::accumulate(c.begin(), c.end(), 0);
    REQUIRE(sum == 4950);
}