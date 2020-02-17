// Variant.cpp
// Demo of std::variant.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Boost /I c:\Dev\Catch2 Variant.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <variant>

struct Type1
{
    Type1() : property_{500}
    {}
    int const property_;
};

struct Type2
{
    Type2() : property_{1000}
    {}
    int const property_;
};

TEST_CASE("std::variant is a type-safe union")
{
    std::variant<Type1, Type2> vary;

    REQUIRE(vary.index() == 0);

    vary.emplace<Type2>();
    REQUIRE(vary.index() == 1);

    REQUIRE(std::get<1>(vary).property_ == 1000);
    REQUIRE(std::get<Type2>(vary).property_ == 1000);

    REQUIRE_THROWS_AS(std::get<0>(vary), std::bad_variant_access);
    REQUIRE_THROWS_AS(std::get<Type1>(vary), std::bad_variant_access);
}

TEST_CASE("std::variant supports visitation")
{
    std::variant<Type1, Type2> vary;
    vary.emplace<Type1>();

    auto double_p = std::visit([](auto& x){ return 2*x.property_; }, vary);
    REQUIRE(double_p == 1000);
}