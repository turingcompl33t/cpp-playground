// Advance.cpp
// Demo of basic std::advance usage.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Catch2 Advance.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <iterator>

#include <list>
#include <vector>
#include <numeric>
#include <forward_list>

TEST_CASE("std::advance() for forward iterators supports iterator increment")
{
    const std::forward_list<int> fl{1, 2, 3};

    auto iter = fl.begin();

    REQUIRE(*iter == 1);
    std::advance(iter, 1);
    REQUIRE(*iter == 2);
    std::advance(iter, 1);
    REQUIRE(*iter == 3);
    std::advance(iter, 1);
    REQUIRE(iter == fl.end());

    // will invoke increment operator necesary number of times
    iter = fl.begin();
    REQUIRE(*iter == 1);
    std::advance(iter, 2);
    REQUIRE(*iter == 3);
}

TEST_CASE("std::advance() for bidirectional iterators supports increment and decrement")
{
    const std::list<int> l{1, 2, 3};

    auto iter = l.begin();

    REQUIRE(*iter == 1);
    std::advance(iter, 1);
    REQUIRE(*iter == 2);
    std::advance(iter, -1);
    REQUIRE(*iter == 1);
    REQUIRE(iter == l.begin());
}

TEST_CASE("std::advance() for random access iterators supports random access operations")
{
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 0);

    auto iter = v.begin();

    REQUIRE(*iter == 0);
    std::advance(iter, 8);
    REQUIRE(*iter == 8);
    std::advance(iter, -8);
    REQUIRE(*iter == 0);
    REQUIRE(iter == v.begin());
}