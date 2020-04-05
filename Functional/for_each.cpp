// for_each.cpp
//
// Demonstration of unique ability of std::for_each() to return
// the function object it was passed.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 for_each.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <numeric>

class MeanValue
{
    long m_count;
    long m_sum;
public:
    MeanValue() : m_count{0}, m_sum{0}
    {}

    void operator()(int e)
    {
        ++m_count;
        m_sum += e;
    }

    double value()
    {
        return static_cast<double>(m_sum) / static_cast<double>(m_count);
    }
};

TEST_CASE("std::for_each() returns the function object it was passed")
{
    auto c = std::vector<int>(9);
    std::iota(std::begin(c), std::end(c), 1); // 1 - 9

    auto mv = std::for_each(std::begin(c), std::end(c), MeanValue{});

    // internal state of the passed function object is preserved
    REQUIRE(mv.value() == 5.0);
}

