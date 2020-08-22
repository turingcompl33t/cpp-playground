// count.cpp
//
// Demo of std::count(), std::count_if()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 count.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <deque>
#include <numeric>
#include <algorithm>

struct SomeType
{
    int m_a;
    int m_b;
    SomeType(int a, int b) : m_a{a}, m_b{b}
    {}

    bool operator==(SomeType const& other)
    {
        return m_a == other.m_a
            && m_b == other.m_b;
    }
};

TEST_CASE("std::count() computes the number of elements in a range \
    that are equivalent to a specified value")
{
    SECTION("works out of the box default with primitive types")
    {
        auto c = std::deque<int>{1, 2, 1, 3};

        auto count = std::count(std::begin(c), std::end(c), 1);

        REQUIRE(count == 2);
    }

    SECTION("and works for types that overload operator==")
    {
        auto c = std::deque<SomeType>{};
        c.emplace_back(1, 1);
        c.emplace_back(2, 2);
        c.emplace_back(1, 1);
        c.emplace_back(3, 3);

        auto count = std::count(std::begin(c), std::end(c), SomeType{1, 1});

        REQUIRE(count == 2);
    }
}

TEST_CASE("std::count_if() computes the number of elements in a range\
    that satisfy a specified predicate")
{
    auto c = std::deque<int>(10);
    std::iota(std::begin(c), std::end(c), 0);  // 0 - 9

    auto odd = [](int i){ return i % 2 != 0; };

    auto const count = std::count_if(std::begin(c), std::end(c), odd);

    REQUIRE(count == 5);
}