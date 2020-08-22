// all_any_none.cpp
//
// Demo of std::all_of(), std::any_of(), std::none_of()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 all_any_none.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <numeric>
#include <algorithm>

TEST_CASE("std::all_of() determines if all of the elements in a range")
{
    SECTION("satisfy a specified predicate")
    {
        auto c1 = std::vector<int>{1, 3, 5};
        auto c2 = std::vector<int>{1, 3, 4};

        auto odd = [](int i){ return i % 2 != 0; };

        REQUIRE(std::all_of(std::begin(c1), std::end(c1), odd));
        REQUIRE_FALSE(std::all_of(std::begin(c2), std::end(c2), odd));
    }
}

TEST_CASE("std::any_of() determines if any of the elements in a range")
{
    SECTION("satisfy a specified predicate")
    {
        auto c1 = std::vector<int>{1, 2, 4};
        auto c2 = std::vector<int>{2, 4, 6};

        auto odd = [](int i){ return i % 2 != 0; };

        REQUIRE(std::any_of(std::begin(c1), std::end(c1), odd));
        REQUIRE_FALSE(std::any_of(std::begin(c2), std::end(c2), odd));
    }
}

TEST_CASE("std::none_of() determines if none of the elements in a range")
{
    SECTION("satisfy a specified predicate")
    {
        auto c1 = std::vector<int>{2, 4, 6};
        auto c2 = std::vector<int>{2, 4, 5};

        auto odd = [](int i){ return i % 2 != 0; };

        REQUIRE(std::none_of(std::begin(c1), std::end(c1), odd));
        REQUIRE_FALSE(std::none_of(std::begin(c2), std::end(c2), odd));
    }
}
