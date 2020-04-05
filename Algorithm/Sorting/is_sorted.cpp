// is_sorted.cpp
//
// Demo of std::is_sorted()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 is_sorted.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <string>
#include <algorithm>

TEST_CASE("std::is_sorted() determines if a given range is in sorted order")
{
    auto c1 = std::vector<int>{1, 2, 3, 4};
    auto c2 = std::vector<int>{4, 3, 2, 1};

    // default function object is < (std::less)
    REQUIRE(std::is_sorted(std::begin(c1), std::end(c1)));  
    REQUIRE_FALSE(std::is_sorted(std::begin(c2), std::end(c2)));

    // manually specify alternative function objects for sort criterion
    REQUIRE_FALSE(std::is_sorted(std::begin(c1), std::end(c1), std::greater{}));
    REQUIRE(std::is_sorted(std::begin(c2), std::end(c2), std::greater{}));
}

TEST_CASE("std::is_sorted() can determine sorted-ness based on user-provided function object")
{
    auto c1 = std::vector<std::string>{"aaa", "bb", "c"};
    auto c2 = std::vector<std::string>{"c", "bb", "aaa"};
    
    REQUIRE(std::is_sorted(std::begin(c1), std::end(c1)));
    REQUIRE(std::is_sorted(std::begin(c2), std::end(c2), 
        [](std::string const& s1, std::string const& s2){
            return s1.length() < s2.length();
        }));
}