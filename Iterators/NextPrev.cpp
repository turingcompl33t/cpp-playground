// NextPrev.cpp
// Demo of basic std::next and std::prev usage.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Catch2 NextPrev.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <iterator>

#include <vector>
#include <numeric>

TEST_CASE("std::next() returns an appropriate iterator")
{
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 0);

    auto iter1 = v.begin();

    REQUIRE(*iter1 == 0);
    
    auto iter2 = std::next(iter1);
    REQUIRE(*iter2 == 1);

    auto iter3 = std::next(iter1, 9);
    REQUIRE(*iter3 == 9);
}

TEST_CASE("std::prev() returns an appropriate iterator")
{
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 0);

    auto iter1 = v.end();
    --iter1;

    REQUIRE(*iter1 == 9);

    auto iter2 = std::prev(iter1);
    REQUIRE(*iter2 == 8);

    auto iter3 = std::prev(iter1, 9);
    REQUIRE(*iter3 == 0);
}