// accum1.cpp
// Using templates with traits types for customization points.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 accum1.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

template <typename T>
T accumulate(T const* beg, T const* end)
{
    auto total = T{};
    while (beg != end)
    {
        total += *beg;
        ++beg;
    }

    return total;
}

TEST_CASE("accumulation function template works with integer collection")
{
    int num[] = {1, 2, 3, 4, 5};
    auto sum = ::accumulate(num, num+5);

    REQUIRE(sum == 15);
}

TEST_CASE("accumulation function template does not work with character collection")
{
    char name[] = "hello";   
    auto length = sizeof(name) - 1;

    auto sum = ::accumulate(name, name+length);

    // 532 is sum of ASCII decimals
    REQUIRE_FALSE(sum == 532);
}