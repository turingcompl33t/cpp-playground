// Any.cpp
// Demo of std::any.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Boost /I c:\Dev\Catch2 Any.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <any>

struct SomeType
{
    SomeType(int p) : property_{p}
    {}
    int const property_;
};

TEST_CASE("std::any allows any_cast to concrete type")
{
    std::any poly;
    poly.emplace<SomeType>(600);

    auto concrete = std::any_cast<SomeType>(poly);
    REQUIRE(concrete.property_ == 600);
    REQUIRE_THROWS_AS(std::any_cast<float>(poly), std::bad_any_cast);
}