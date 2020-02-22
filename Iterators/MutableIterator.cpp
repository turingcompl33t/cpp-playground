// MutableIterator.cpp
// Demo of basic mutable iterator usage.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Catch2 MutableIterator.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>

TEST_CASE("mutable iterators allow writing")
{
    std::vector<int> v{1, 2, 3};  // cannot be const
    auto iter = v.begin();

    REQUIRE(iter == v.begin());
    REQUIRE(*iter == 1);
    ++iter;
    REQUIRE(*iter == 2);
    *iter = 77;
    REQUIRE(*iter == 77);
    ++iter;
    REQUIRE(*iter == 3);
    *iter = 99;
    REQUIRE(*iter == 99);
    ++iter;
    REQUIRE(iter == v.end());
}

TEST_CASE("mutable iterators support the index[] operator")
{
    std::vector<int> v{1, 2, 3};  // cannot be const
    auto iter = v.begin();

    REQUIRE(iter == v.begin());
    iter[1] = 99;
    REQUIRE(*iter == 1);
    ++iter;
    REQUIRE(*iter == 99);
}
