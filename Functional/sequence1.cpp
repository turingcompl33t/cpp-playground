// sequence1.cpp
//
// Function objects in sequence generation.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 sequence1.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <list>
#include <iterator>
#include <algorithm>

class IntegerSequence
{
    int m_value;
public:
    IntegerSequence(int init) : m_value{init}
    {}

    int operator()()
    {
        return m_value++;
    }
};

TEST_CASE("algorithm makes copy of the passed function object so internal state is unchanged by call")
{   
    auto c = std::list<int>{};
    auto seq = IntegerSequence{1};

    std::generate_n(
        std::back_inserter(c),
        3,
        seq
        );

    REQUIRE(c.size() == 3);

    auto i1 = c.begin();
    REQUIRE((*i1++) == 1);
    REQUIRE((*i1++) == 2);
    REQUIRE((*i1++) == 3);

    std::generate_n(
        std::back_inserter(c),
        3,
        seq
        );

    auto i2 = c.begin();
    std::advance(i2, 3);
    REQUIRE((*i2++) == 1);
    REQUIRE((*i2++) == 2);
    REQUIRE((*i2++) == 3);
}

TEST_CASE("can force algorithm to modify internal state of function object by passing by reference")
{
    auto c = std::list<int>{};
    auto seq = IntegerSequence{1};

    std::generate_n(
        std::back_inserter(c),
        3,
        std::ref(seq)
        );

    REQUIRE(c.size() == 3);

    auto i1 = c.begin();
    REQUIRE((*i1++) == 1);
    REQUIRE((*i1++) == 2);
    REQUIRE((*i1++) == 3);

    std::generate_n(
        std::back_inserter(c),
        3,
        std::ref(seq)
        );

    auto i2 = c.begin();
    std::advance(i2, 3);
    REQUIRE((*i2++) == 4);
    REQUIRE((*i2++) == 5);
    REQUIRE((*i2++) == 6);
}