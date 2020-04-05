// composability.cpp
// Demo of basic range utility: composability.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++latest /permissive- /experimental:preprocessor /I %CPP_WORKSPACE%\_Deps\Catch2 /I %CPP_WORKSPACE%\_Deps\RangeV3\Include composability.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <numeric>
#include <algorithm>

#include <range/v3/all.hpp>

TEST_CASE("ranges enable simple and elegant composition of operations on containers")
{
    auto v = std::vector<int>(10);
    std::iota(v.begin(), v.end(), 0);

    // filter out odd values,
    // filter out values less than 4,
    // and square remaining values
    auto r = v | ranges::views::remove_if([](int i){ return i % 2 != 0; })
               | ranges::views::remove_if([](int i){ return i < 4; })
               | ranges::views::transform([](int i){ return i*i; })
               | ranges::to<std::vector>();  

    auto expected = std::vector<int>{16, 36, 64};
    
    REQUIRE(r.size() == expected.size());
    REQUIRE(std::equal(r.begin(), r.end(), expected.begin()));
}