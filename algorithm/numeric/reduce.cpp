// reduce.cpp
//
// Demo of std::reduce()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 reduce.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <numeric>
#include <algorithm>

template <typename Iter, typename T>
auto equal_to(Iter beg, Iter end, T const& val) -> int
{
    return std::reduce(beg, end, 0, 
        [val](auto a, auto b){ return a + (b == val); });
}

TEST_CASE("std::reduce()")
{
    auto c = std::vector<int>{2, 3, 4, 3, 4, 6, 3};

    int count = equal_to(c.begin(), c.end(), 3);

    REQUIRE(count == 3);
}
