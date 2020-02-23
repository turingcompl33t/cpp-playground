// Construction.cpp
// Demo of basic string construction.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Catch2 Construction.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>
#include <vector>
#include <utility>

TEST_CASE("std::string supports construction")
{
    SECTION("empty string")
    {
        std::string str{};
        REQUIRE(str.empty());
    }

    SECTION("repeated characters")
    {
        std::string str(3, 'a');
        REQUIRE(str == "aaa");
    }

    SECTION("char*")
    {
        auto source = "hello world";
        
        std::string str1{source};
        std::string str2(source, 5);

        REQUIRE(str1 == "hello world");
        REQUIRE(str2 == "hello");
    }

    SECTION("copy construction")
    {
        std::string source{"hello world"};

        std::string str1{source};
        std::string str2 = source;

        REQUIRE(str1 == source);
        REQUIRE(str2 == source);
    }

    SECTION("move construction")
    {
        std::string source{"hello world"};

        std::string str1{std::move(source)};
        REQUIRE(str1 == "hello world");

        std::string str2 = std::move(str1);
        REQUIRE(str2 == "hello world");
    }

    SECTION("construction from substrings")
    {
        std::string source{"hello world"};

        std::string str1(source, 0, 5);
        std::string str2(source, 6);

        REQUIRE(str1 == "hello");
        REQUIRE(str2 == "world");
    }

    SECTION("construction from arbitrary container elements")
    {
        std::vector<char> v{'h', 'e', 'l', 'l', 'o'};
        std::string str{std::begin(v), std::end(v)};

        REQUIRE(str == "hello");
    }
}