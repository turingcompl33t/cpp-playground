// reduce.cpp
// Usage of std::reduce()

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <vector>
#include <numeric>
#include <algorithm>

// really just std::count_if()
template <typename Iter, typename T>
auto equal_to(Iter beg, Iter end, T const& val) -> std::size_t
{
    return std::reduce(beg, end, 0, 
        [val](auto a, auto b){ return a + (b == val); });
}

TEST_CASE("std::reduce() behaves similarly to std::accumulate, but we can omit the initializer")
{
    auto v = std::vector<int>(10);
    std::iota(v.begin(), v.end(), 0);

    auto const r = std::reduce(v.cbegin(), v.cend());
    REQUIRE(r == 45);
}
