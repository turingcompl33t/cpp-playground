// search.cpp
//
// Demo of std::search()
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 search.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <list>
#include <string>
#include <numeric>
#include <algorithm>

TEST_CASE("std::search() searches a range for a specified subrange")
{
    SECTION("based on operator==")
    {
        auto c = std::list<int>(10);
        std::iota(std::begin(c), std::end(c), 0); // 0 -9

        auto t = std::list<int>{4, 5, 6};

        auto it = std::search(
            std::begin(c), std::end(c), 
            std::begin(t), std::end(t));

        REQUIRE(*it == 4);
        REQUIRE(*++it == 5);
        REQUIRE(*++it == 6);
    }

    SECTION("based on binary predicate")
    {
        auto c = std::list<int>(10);
        std::iota(std::begin(c), std::end(c), 0); // 0 - 9

        auto t = std::list<int>{6, 5, 4};

        auto sum_to_10 = [](int i1, int i2){ return i1 + i2 == 10; };

        auto it = std::search(
            std::begin(c), std::end(c),
            std::begin(t), std::end(t),
            sum_to_10); 

        REQUIRE(*it == 4);
        REQUIRE(*++it == 5);
        REQUIRE(*++it == 6);
    }
}

bool contains_substring(std::string const& str, std::string const& pattern)
{
    return std::search(
        std::begin(str), std::end(str), 
        std::begin(pattern), std::end(pattern)) != std::end(str);
}

TEST_CASE("std::search() can be used to implement substring search")
{
    using namespace std::string_literals;

    auto sentence = "I am a man of perfect simplicity"s;

    REQUIRE(::contains_substring(sentence, "I am a"));
    REQUIRE(::contains_substring(sentence, "perfect simplicity"));
    REQUIRE_FALSE(::contains_substring(sentence, "perfect insanity"));
}

TEST_CASE("std::search() returns begin when test sequence is empty and")
{
    SECTION("target sequence is nonempty")
    {
        auto const s1 = std::string{"hello"};
        auto const s2 = std::string{""};

        auto r = std::search(s1.begin(), s1.end(), s2.begin(), s2.end());

        REQUIRE(r == s1.begin());
        REQUIRE(r != s1.end());
    }

    SECTION("target sequence is also empty")
    {
        auto const s1 = std::string{""};
        auto const s2 = std::string{""};

        auto r = std::search(s1.begin(), s1.end(), s2.begin(), s2.end());
        
        REQUIRE(r == s1.begin());
        REQUIRE(r == s1.end());
    }
}