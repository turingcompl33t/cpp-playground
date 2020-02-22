// BidirectionalIterator.cpp
// Demo of basic bidirectional iterator usage.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Catch2 BidirectionalIterator.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <list>

TEST_CASE("std::list begin() and end() provide bidirectional iterators")
{
    std::list<int> l{1, 2, 3};
    auto iter = l.begin();

    REQUIRE(iter == l.begin());
    REQUIRE(*iter == 1);
    ++iter;
    REQUIRE(*iter == 2);
    --iter;
    REQUIRE(*iter == 1);
    REQUIRE(iter == l.begin());
}