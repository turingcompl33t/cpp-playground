// stable_sort.cpp
//
// Demo fo std::stable_sort()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 stable_sort.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <algorithm>
#include <iostream>

TEST_CASE("std::stable_sort()")
{
    auto c = std::vector<std::string>{ "cat", "bear", "deer", "dog", "elephant", "ox" };

    // sort criterion
    auto str_len = [](std::string const& a, std::string const& b)
        { 
            return a.length() < b.length(); 
        };

    // sort on length, preserving relative ordering of equal-length elements
    std::stable_sort(c.begin(), c.end(), str_len);

    REQUIRE(c[1] == "cat");
    REQUIRE(c[2] == "dog");
}