// construction.cpp
// Demo of basic std::string constructor semantics.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Catch2 construction.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>
#include <vector>
#include <utility>

TEST_CASE("std::string supports construction")
{
    SECTION("empty string")
    {
        auto str = std::string{};
        REQUIRE(str.empty());
    }

    SECTION("repeated characters")
    {
        auto str = std::string(3, 'a');
        REQUIRE(str == "aaa");
    }

    SECTION("char*")
    {
        auto source = "hello world";
        
        auto str1 = std::string{source};
        auto str2 = std::string(source, 5);

        REQUIRE(str1 == "hello world");
        REQUIRE(str2 == "hello");
    }

    SECTION("copy construction")
    {
        auto src = std::string{"hello world"};

        auto str1 = std::string{src};
        auto str2 = src;

        REQUIRE(str1 == src);
        REQUIRE(str2 == src);
    }

    SECTION("move construction")
    {
        auto src = std::string{"hello world"};

        auto str1 = std::string{std::move(src)};
        REQUIRE(str1 == "hello world");

        auto str2 = std::move(str1);
        REQUIRE(str2 == "hello world");
    }

    SECTION("construction from substrings")
    {
        auto src = std::string{"hello world"};

        auto str1 = std::string(src, 0, 5);
        auto str2 = std::string(src, 6);

        REQUIRE(str1 == "hello");
        REQUIRE(str2 == "world");
    }

    SECTION("construction from arbitrary container elements")
    {
        auto v = std::vector<char>{'h', 'e', 'l', 'l', 'o'};
        auto str = std::string{std::begin(v), std::end(v)};

        REQUIRE(str == "hello");
    }
}