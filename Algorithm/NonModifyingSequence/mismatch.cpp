// mismatch.cpp
//
// Demo of std::mismatch()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 mismatch.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <list>
#include <algorithm>

TEST_CASE("std::mismatch() computes the first position at \
    which two ranges differ based on value")
{
    auto c1 = std::list<int>{1, 2, 3, 4, 5};
    auto c2 = std::list<int>{};

    std::copy(std::begin(c1), std::end(c1), std::back_inserter(c2));

    c1.push_back(1337);
    c2.push_back(1054);

    auto pos = std::mismatch(std::begin(c1), std::end(c1), std::begin(c2));

    REQUIRE(*pos.first == 1337);
    REQUIRE(*pos.second == 1054);
}

TEST_CASE("std::mismatch() computes the first position at \
    which two ranges differ based on binary predicate")
{
    auto c1 = std::list<int>{1, 2, 3, 4, 5};
    auto c2 = std::list<int>{};

    std::transform(std::begin(c1), std::end(c1), 
        std::back_inserter(c2),
        [](int i){ return 10 - i; });

    c1.push_back(7);
    c2.push_back(4);

    auto sum_to_10 = [](int i1, int i2){ return i1 + i2 == 10; };

    auto pos = std::mismatch(std::begin(c1), std::end(c1), std::begin(c2), sum_to_10);

    REQUIRE(*pos.first == 7);
    REQUIRE(*pos.second == 4);
}

TEST_CASE("std::mismatch() returns a pair containing an end iterator \
    and the corresponding ieterator in the other range if no mismatches are found")
{
    auto c1 = std::list<int>{1, 2, 3, 4, 5};
    auto c2 = std::list<int>{};

    std::copy(std::begin(c1), std::end(c1), std::back_inserter(c2));

    // UB if second range is shorter than the first
    c2.push_back(6);

    auto pos = std::mismatch(std::begin(c1), std::end(c1), std::begin(c2));

    REQUIRE(pos.first == std::end(c1));
    REQUIRE(*pos.second == 6);
}