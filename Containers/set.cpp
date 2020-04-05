// set.cpp
// Demo of basic properties and usage of std::set and std::multiset.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 set.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <set>
#include <array>
#include <tuple>

TEST_CASE("std::set supports construction")
{
    SECTION("default construction")
    {
        auto c = std::set<int>{};
        REQUIRE(c.empty());
    }

    SECTION("construction with specified sorting criterion")
    {
        auto c = std::set<int, std::greater<int>>{std::greater<int>()};
        REQUIRE(c.empty());
    }

    SECTION("construction from range")
    {
        auto src = std::array<int, 3>{1, 2, 3};
        auto dst = std::set<int>{std::begin(src), std::end(src)};

        REQUIRE(dst.size() == 3);
        REQUIRE(dst.find(1) == dst.begin());
    }

    SECTION("construction from range with specified sorting criterion")
    {
        auto src = std::array<int, 3>{1, 2, 3};
        auto dst = std::set<int, std::greater<int>>{
            std::begin(src), 
            std::end(src), 
            std::greater<int>()
            };

        REQUIRE(dst.size() == 3);
        REQUIRE(dst.find(1) == --dst.end());
    }

    SECTION("construction from initializer list")
    {
        auto c1 = std::set<int>{1, 2, 3};

        REQUIRE(c1.size() == 3);
        REQUIRE(c1.find(1) == c1.begin());

        // alternative syntax for the same thing
        std::set<int> c2 = {1, 2, 3};

        REQUIRE(c2.size() == 3);
        REQUIRE(c2.find(1) == c2.begin());
    }

    SECTION("copy construction")
    {
        auto src = std::set<int>{1, 2, 3};
        auto dst = std::set<int>{src};

        REQUIRE(dst.size() == src.size());
        REQUIRE(dst == src);
    }

    SECTION("copy assignment")
    {
        auto src = std::set<int>{1, 2, 3};
        auto dst = src;

        REQUIRE(dst.size() == src.size());
        REQUIRE(dst == src);
    }

    SECTION("move construction")
    {
        auto src = std::set<int>{1, 2, 3};
        auto dst = std::set<int>{std::move(src)};

        REQUIRE(dst.size() == 3);
        REQUIRE(dst.find(1) == dst.begin());
    }

    SECTION("move assignment")
    {
        auto src = std::set<int>{1, 2, 3};
        auto dst = std::move(src);

        REQUIRE(dst.size() == 3);
        REQUIRE(dst.find(1) == dst.begin());
    }

    SECTION("swap() and std::swap()")
    {
        auto c1 = std::set<int>{1, 2, 3};
        auto c2 = std::set<int>{4, 5, 6};

        c1.swap(c2);
        REQUIRE(*c1.begin() == 4);
        REQUIRE(*c2.begin() == 1);

        std::swap(c1, c2);
        REQUIRE(*c1.begin() == 1);
        REQUIRE(*c2.begin() == 4);
    }
}

TEST_CASE("search operations on std::set")
{
    SECTION("find()")
    {
        auto c = std::set<int>{1, 2, 3};

        REQUIRE(c.find(1) == c.begin());
        REQUIRE(*c.find(1) == 1);
        REQUIRE(c.find(17) == c.end());
    }

    SECTION("count()")
    {
        auto c = std::set<int>{1, 2, 3};
        
        REQUIRE(c.count(2) == 1);
        REQUIRE(c.count(5) == 0);
    }

    SECTION("lower_bound()")
    {
        auto c = std::set<int>{2, 4, 6, 8, 10};

        REQUIRE(*c.lower_bound(5) == 6);
        REQUIRE(*c.lower_bound(4) == 4);
    }

    SECTION("upper_bound()")
    {
        auto c = std::set<int>{2, 4, 6, 8, 10};

        REQUIRE(*c.upper_bound(5) == 6);
        REQUIRE(*c.upper_bound(4) == 6);  // note the difference when queried value is present
    }

    SECTION("equal_range()")
    {
        auto c = std::set<int>{2, 4, 6, 8, 10};

        auto r1 = c.equal_range(5);
        REQUIRE(*r1.first == 6);
        REQUIRE(*r1.second == 6);

        auto r2 = c.equal_range(4);
        REQUIRE(*r2.first == 4);
        REQUIRE(*r2.second == 6);
    }
}

TEST_CASE("element insert and removal")
{
    SECTION("single element insert")
    {
        auto c = std::set<int>{};
        c.insert(1);

        REQUIRE(*c.begin() == 1);
    }

    SECTION("range insert")
    {
        auto c = std::set<int>{};
        auto a = std::array<int, 3>{1, 2, 3};

        c.insert(std::begin(a), std::end(a));

        REQUIRE(*c.begin() == 1);
        REQUIRE(*(--c.end()) == 3);
    }

    SECTION("initializer list insert")
    {
        auto c = std::set<int>{};
        c.insert({1, 2, 3});

        REQUIRE(*c.begin() == 1);
        REQUIRE(*(--c.end()) == 3);
    }

    SECTION("emplacement")
    {
        auto c = std::set<std::pair<int, int>>{};

        c.emplace(1, 2);

        REQUIRE((*c.begin()).first == 1);
        REQUIRE((*c.begin()).second == 2);
    }

    SECTION("value erasure")
    {
        auto c = std::set<int>{1, 2, 3};
        REQUIRE(*c.begin() == 1);

        c.erase(1);
        REQUIRE(*c.begin() == 2);
    }

    SECTION("range erasure")
    {
        auto c = std::set<int>{0, 2, 4, 6, 8};

        auto it = c.begin();
        std::advance(it, 2);

        c.erase(c.begin(), it);

        REQUIRE(*c.begin() == 4);
        REQUIRE(c.size() == 3);
    }

    SECTION("clear()")
    {
        auto c = std::set<int>{1, 2, 3, 4, 5};

        REQUIRE_FALSE(c.empty());

        c.clear();

        REQUIRE(c.empty());
    }
}

TEST_CASE("std::set maintains elements in sorted order")
{
    auto c = std::set<int>{};

    for (auto i = 10; i >= 0; --i)
    {
        c.insert(i);
    }

    REQUIRE(*c.begin() == 0);
    REQUIRE(std::is_sorted(c.begin(), c.end()));
}

using string_compare_alpha = std::less<std::string>;

struct string_compare_length
{
    bool operator()(std::string const& s1, std::string const& s2) const
    {
        return s1.length() < s2.length();
    }
};

TEST_CASE("std::set supports custom sort criterion")
{
    auto c1 = std::set<std::string, string_compare_alpha>{string_compare_alpha()};
    auto c2 = std::set<std::string, string_compare_length>{string_compare_length()};

    auto strings = std::array<std::string, 3>{"aaa", "bb", "c"};

    for (auto const& s : strings)
    {
        c1.insert(s);
        c2.insert(s);
    }

    REQUIRE(*c1.begin() == "aaa");
    REQUIRE(*c2.begin() == "c");
}

TEST_CASE("std::multiset supports duplicate elements")
{
    auto s = std::set<int>{1, 2, 3};
    auto m = std::multiset<int>{1, 2, 3};

    // set insert fails on duplicate
    REQUIRE_FALSE(s.insert(2).second);
    m.insert(2);

    REQUIRE(s.size() == 3);
    REQUIRE(m.size() == 4);
}