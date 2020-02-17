// Pair.cpp
// Demo of std::pair.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Boost /I c:\Dev\Catch2 Pair.cpp

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

Type1 instance_1{ "type_1" };
Type2 instance_2{ "type_2" };

TEST_CASE("std::pair permits access to members")
{
    std::pair<Type1, Type2> pair{instance_1, instance_2};
    REQUIRE(pair.first.identifier_ == instance_1.identifier_);
    REQUIRE(pair.second.identifier_ == instance_2.identifier_);
}

TEST_CASE("std::pair works with structured bindings")
{
    std::pair<Type1, Type2> pair{instance_1, instance_2};
    auto& [ref_1, ref_2] = pair;
    REQUIRE(ref_1.identifier_ == instance_1.identifier_);
    REQUIRE(ref_2.identifier_ == instance_2.identifier_);
}

TEST_CASE("std::pair supports make_pair() convenience function")
{
    auto pair = std::make_pair(instance_1, instance_2);
    REQUIRE(pair.first.identifier_ == instance_1.identifier_);
    REQUIRE(pair.second.identifier_ == instance_2.identifier_);
}