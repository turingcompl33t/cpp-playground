// iota.cpp
//
// Demo of std::iota()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 iota.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <numeric>

TEST_CASE("std::iota()")
{
    auto c1 = std::vector<int>(10);
    auto c2 = std::vector<int>(10);

    std::iota(c1.begin(), c1.end(), 0);
    std::iota(c2.begin(), c2.end(), -5);

    REQUIRE(c1.front() == 0);
    REQUIRE(c1.back() == 9);

    REQUIRE(c2.front() == -5);
    REQUIRE(c2.back() == 4);
}