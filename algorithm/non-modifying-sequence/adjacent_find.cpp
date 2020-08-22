// adjacent_find.cpp
//
// Demo of std::adjacent_find()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 adjacent_find.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <algorithm>

struct SomeType
{
    int m_v;
    SomeType(int v) : m_v{v}
    {}

    bool operator==(SomeType const& other)
    {   
        // some pathological definition of equivalence...
        return m_v + other.m_v == 10;
    }
};

TEST_CASE("std::adjacent_find() finds the first adjacent pair of elements in a range that")
{
    SECTION("are equivalent")
    {
        auto c = std::vector<int>{1, 2, 3, 4, 4, 5};

        auto it = std::adjacent_find(std::begin(c), std::end(c));

        // returns iterator to first in the adjacent pair
        REQUIRE(*it == 4);
        REQUIRE(*(--it) == 3);
    }

    SECTION("are equivalent based on operator== overload")
    {
        auto c = std::vector<SomeType>{};
        c.emplace_back(1);
        c.emplace_back(2);
        c.emplace_back(4);
        c.emplace_back(6);
        c.emplace_back(9);

        auto it = std::adjacent_find(std::begin(c), std::end(c));

        REQUIRE((*it).m_v == 4);
        REQUIRE((*++it).m_v == 6);
    }

    SECTION("satisfy a given binary predicate")
    {
        auto c = std::vector<int>{1, 2, 4, 6, 9};

        auto sum_to_10 = [](int i1, int i2){ return i1 + i2 == 10; };

        auto it = std::adjacent_find(std::begin(c), std::end(c), sum_to_10);

        REQUIRE(*it == 4);
        REQUIRE(*++it == 6);
    }
}