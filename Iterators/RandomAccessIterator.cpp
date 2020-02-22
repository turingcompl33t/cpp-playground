// RandomAccessIterator.cpp
// Demo of basic random access iterator usage.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Catch2 RandomAccessIterator.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>

TEST_CASE("std::vector begin() and end() provide random access iterators")
{
    std::vector<int> v{1, 2, 3};
    auto iter = v.begin();

    REQUIRE(iter == v.begin());
    REQUIRE(*iter == 1);
    iter += 2;
    REQUIRE(*iter == 3);
    ++iter;
    REQUIRE(iter == v.end());
}