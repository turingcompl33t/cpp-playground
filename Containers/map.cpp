// map.cpp
// Demo of basic properties and usage of std::map and std::multimap.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 map.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <map>
#include <array>
#include <tuple>

TEST_CASE("std::map supports construction")
{
    SECTION("default construction")
    {
        auto c = std::map<int, int>{};
        REQUIRE(c.empty());
    }

    SECTION("construction with specified sort criterion")
    {
        auto c = std::map<int, int, std::greater<int>>{std::greater<int>()};
        REQUIRE(c.empty());
    }

    SECTION("construction from range")
    {
        auto a = std::array<std::pair<int, int>, 3>{
            std::make_pair(1, 1),
            std::make_pair(2, 2),
            std::make_pair(3, 3)
            };

        auto c = std::map<int, int>{std::begin(a), std::end(a)};

        REQUIRE(c.size() == 3);
        REQUIRE((*c.begin()).first == 1);
        REQUIRE((*c.begin()).second == 1);
    }

    SECTION("construction from initializer list")
    {
        auto c = std::map<int, int>{
            std::make_pair(1, 1),
            std::make_pair(2, 2),
            std::make_pair(3, 3)
        };

        REQUIRE(c.size() == 3);
        REQUIRE((*c.begin()).first == 1);
        REQUIRE((*c.begin()).second == 1);
    }

    SECTION("copy construction")
    {
        auto src = std::map<int, int>{
            std::make_pair(1, 1),
            std::make_pair(2, 2),
            std::make_pair(3, 3)
        };

        auto dst = std::map<int, int>{src};
        
        REQUIRE(dst.size() == 3);
        REQUIRE((*dst.begin()).first == 1);
        REQUIRE((*dst.begin()).second == 1);
    }

    SECTION("copy assignment")
    {
        auto src = std::map<int, int>{
            std::make_pair(1, 1),
            std::make_pair(2, 2),
            std::make_pair(3, 3)
        };

        auto dst = src;
        
        REQUIRE(dst.size() == 3);
        REQUIRE((*dst.begin()).first == 1);
        REQUIRE((*dst.begin()).second == 1);
    }

    SECTION("move construction")
    {
        auto src = std::map<int, int>{
            std::make_pair(1, 1),
            std::make_pair(2, 2),
            std::make_pair(3, 3)
        };

        auto dst = std::map<int, int>{std::move(src)};
        
        REQUIRE(dst.size() == 3);
        REQUIRE((*dst.begin()).first == 1);
        REQUIRE((*dst.begin()).second == 1);
    }

    SECTION("move assignment")
    {
        auto src = std::map<int, int>{
            std::make_pair(1, 1),
            std::make_pair(2, 2),
            std::make_pair(3, 3)
        };

        auto dst = std::move(src);
        
        REQUIRE(dst.size() == 3);
        REQUIRE((*dst.begin()).first == 1);
        REQUIRE((*dst.begin()).second == 1);
    }

    SECTION("swap() and std::swap()")
    {
        auto c1 = std::map<int, int>{
            std::make_pair(1, 1),
            std::make_pair(2, 2),
            std::make_pair(3, 3)
        };

        auto c2 = std::map<int, int>{
            std::make_pair(4, 4),
            std::make_pair(5, 5),
            std::make_pair(6, 6)
        };

        c1.swap(c2);

        REQUIRE((*c1.begin()).first == 4);
        REQUIRE((*c2.begin()).first == 1);

        std::swap(c1, c2);

        REQUIRE((*c1.begin()).first == 1);
        REQUIRE((*c2.begin()).first == 4);
    }
}

TEST_CASE("std::map supports static initialization")
{
    std::map<std::string, int> const m
    {
        {"hello", 0},
        {"world", 1}
    };

    auto r1 = m.find("hello");
    auto r2 = m.find("world");

    REQUIRE((*r1).second == 0);
    REQUIRE((*r2).second == 1);
}

TEST_CASE("search operations on std::map")
{
    SECTION("find()")
    {
        auto c = std::map<int, int>{
            std::make_pair(1, 1),
            std::make_pair(2, 2),
            std::make_pair(3, 3)
        };

        REQUIRE(c.find(1) == c.begin());
        REQUIRE(*c.find(1) == std::pair<int const, int>{1, 1});
        REQUIRE(c.find(17) == c.end());
    }

    SECTION("count()")
    {
        auto c = std::map<int, int>{
            std::make_pair(1, 1),
            std::make_pair(2, 2),
            std::make_pair(3, 3)
        };

        REQUIRE(c.count(2) == 1);
        REQUIRE(c.count(5) == 0);
    }

    SECTION("lower_bound()")
    {
        auto c = std::map<int, int>{
            std::make_pair(1, 1),
            std::make_pair(2, 2),
            std::make_pair(3, 3),
            std::make_pair(5, 5)
        };

        REQUIRE(*c.lower_bound(2) == std::pair<int const, int>{2, 2});
        REQUIRE(*c.lower_bound(4) == std::pair<int const, int>{5, 5});
    }

    SECTION("upper_bound()")
    {
        auto c = std::map<int, int>{
            std::make_pair(1, 1),
            std::make_pair(2, 2),
            std::make_pair(3, 3),
            std::make_pair(5, 5)
        };

        REQUIRE(*c.upper_bound(2) == std::pair<int const, int>{3, 3});
        REQUIRE(*c.upper_bound(3) == std::pair<int const, int>{5, 5});
    }

    SECTION("equal_range()")
    {
        auto c = std::map<int, int>{
            std::make_pair(1, 1),
            std::make_pair(2, 2),
            std::make_pair(3, 3),
            std::make_pair(5, 5)
        };

        // equal_range() returns a pair of keys (which are themselves pairs)
        auto r1 = c.equal_range(2);
        REQUIRE((*r1.first).first == 2);
        REQUIRE((*r1.second).first == 3);
    }
}

TEST_CASE("insertion into std::map")
{
    SECTION("using value_type")
    {
        auto c = std::map<std::string, int>{};

        c.insert(
            std::map<std::string, int>::value_type{"hello", 1}
        );

        REQUIRE((*c.begin()).first == "hello");
    }

    SECTION("using std::pair directly")
    {
        auto c = std::map<std::string, int>{};

        c.insert(std::pair<std::string, int>{"hello", 1});
        c.insert(std::pair<std::string, int>{"world", 2});

        REQUIRE((*c.begin()).first == "hello");
        REQUIRE((*++c.begin()).first == "world");
    }

    SECTION("using std::make_pair()")
    {
        auto c = std::map<std::string, int>{};

        c.insert(std::make_pair("hello", 1));
        c.insert(std::make_pair("world", 2));

        REQUIRE((*c.begin()).first == "hello");
        REQUIRE((*++c.begin()).first == "world");
    }

    SECTION("using insert() with initializer list")
    {
        auto c = std::map<std::string, int>{};

        c.insert({"hello", 1});
        c.insert({"world", 2});

        REQUIRE((*c.begin()).first == "hello");
        REQUIRE((*++c.begin()).first == "world");
    }

    SECTION("using emplace()")
    {
        auto c = std::map<std::string, int>{};

        c.emplace("hello", 1);
        c.emplace("world", 2);

        REQUIRE((*c.begin()).first == "hello");
        REQUIRE((*++c.begin()).first == "world");
    }
}

using string_compare_alpha = std::less<std::string>;

struct string_compare_length
{
    bool operator()(std::string const& s1, std::string const& s2) const
    {
        return s1.length() < s2.length();
    }
};

TEST_CASE("std::map supports custom sort criterion")
{
    auto c1 = std::map<std::string, int, string_compare_alpha>{string_compare_alpha()};
    auto c2 = std::map<std::string, int, string_compare_length>{string_compare_length()};

    auto strings = std::array<std::string, 3>{"aaa", "bb", "c"};

    for (auto const& s : strings)
    {  
        // value for each key is immaterial
        c1.emplace(s, 1);
        c2.emplace(s, 1);
    }

    REQUIRE((*c1.begin()).first == "aaa");
    REQUIRE((*c2.begin()).first == "c");
}