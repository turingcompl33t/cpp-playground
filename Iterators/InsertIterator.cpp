// InsertIterator.cpp
// Demo of basic insert iterator usage.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 InsertIterator.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <deque>
#include <iterator>

TEST_CASE("Insert iterators convert writes into container insertions")
{
    std::deque<int> dq{};
    auto back_inserter = std::back_inserter(dq);
    *back_inserter = 2;  // 2
    ++back_inserter;
    *back_inserter = 3;  // 2 3
    ++back_inserter;

    REQUIRE(dq[0] == 2);
    REQUIRE(dq[1] == 3);

    auto front_inserter = std::front_inserter(dq);
    *front_inserter = 1;  // 1 2 3
    ++front_inserter;
    *front_inserter = 0;  // 0 1 2 3
    ++front_inserter;

    REQUIRE(dq[0] == 0);
    REQUIRE(dq[1] == 1);

    auto inserter = std::inserter(dq, dq.begin()+2);
    *inserter = 77;  // 0 1 2 77 3
    ++inserter;
    *inserter = 99;  // 0 1 2 77 99 3
    ++inserter;

    REQUIRE(dq[2] == 77);
    REQUIRE(dq[3] == 99);
}   


