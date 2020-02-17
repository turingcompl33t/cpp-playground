// Tuple.cpp
// Demo of std::tuple.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Boost /I c:\Dev\Catch Tuple.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <utility>

struct Type1
{
    char const* identifier_;
};

struct Type2
{
    char const* identifier_;
};

struct Type3
{
    char const* identifier_;
};

Type1 instance_1{ "type_1" };
Type2 instance_2{ "type_2" };
Type3 instance_3{ "type_3" };

TEST_CASE("std::tuple permits access to members with std::get")
{
    using triple = std::tuple<Type1, Type2, Type3>;

    triple trio{instance_1, instance_2, instance_3};

    REQUIRE(std::get<0>(trio).identifier_ == instance_1.identifier_);
    REQUIRE(std::get<Type1>(trio).identifier_ == instance_1.identifier_);

    REQUIRE(std::get<1>(trio).identifier_ == instance_2.identifier_);
    REQUIRE(std::get<Type2>(trio).identifier_ == instance_2.identifier_);

    REQUIRE(std::get<2>(trio).identifier_ == instance_3.identifier_);
    REQUIRE(std::get<Type3>(trio).identifier_ == instance_3.identifier_);
}