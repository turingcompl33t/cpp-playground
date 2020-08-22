// is_sorted_until.cpp
//
// Demo of std::is_sorted_until()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 is_sorted_until.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <list>
#include <string>
#include <algorithm>

TEST_CASE("std::is_sorted_until() returns an iterator to the \
    upper bound of the subrange for which the range is sorted")
{
    auto c = std::list<int>{1, 2, 3, 4, 0, 5, 6, 7};

    auto it = std::is_sorted_until(std::begin(c), std::end(c));

    REQUIRE(*it == 0);
    REQUIRE(std::distance(std::begin(c), it) == 4);
}

TEST_CASE("std::is_sorted_until() accepts a user-defined function object")
{
    auto c = std::list<std::string>{"a", "bb", "ccc", "dd", "eee", "f"};

    auto it = std::is_sorted_until(std::begin(c), std::end(c),
        [](std::string const& s1, std::string const& s2)
        {
            return s1.length() < s2.length();
        });

    REQUIRE(*it == "dd");
    REQUIRE(std::distance(std::begin(c), it) == 3);
}