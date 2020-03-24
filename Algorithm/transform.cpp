// transform.cpp
//
// Demo of std::transform()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 transform.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <numeric>
#include <vector>
#include <algorithm>

TEST_CASE("std::transform()")
{
    auto c = std::vector<int>(10);
    std::iota(c.begin(), c.end(), 0);  // 0 - 9

    // squares all the elements in c
    std::transform(c.begin(), c.end(), c.begin(), 
        [](int const i) -> int { return i*i; });

    REQUIRE(c.size() == 10);
    REQUIRE(c.back() == 81);
}