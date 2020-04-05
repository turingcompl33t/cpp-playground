// set_operations.cpp
//
// Demo of STL set operations
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 set_operations.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <numeric>
#include <algorithm>

TEST_CASE("std::set_union()")
{
    auto c1 = std::vector<int>(10);
    auto c2 = std::vector<int>(10);
    auto r = std::vector<int>{};

    std::iota(c1.begin(), c1.end(), 0);   // 0 - 9
    std::iota(c2.begin(), c2.end(), -5);  // -5 - 4

    // compute the set union of c1 and c2
    // insert results into result vector r
    std::set_union(c1.begin(), c1.end(), c2.begin(), c2.end(), std::back_inserter(r));

    REQUIRE(r.size() == 15);
}

TEST_CASE("std::set_intersection()")
{
    auto c1 = std::vector<int>(10);
    auto c2 = std::vector<int>(10);
    auto r = std::vector<int>{};

    std::iota(c1.begin(), c1.end(), 0);   // 0 - 9
    std::iota(c2.begin(), c2.end(), -5);  // -5 - 4

    // compute the set intersection between c1 and c2
    // insert results into result vector r
    std::set_intersection(c1.begin(), c1.end(), c2.begin(), c2.end(), std::back_inserter(r));

    REQUIRE(r.size() == 5);  // note: complement of set_union() result size
}