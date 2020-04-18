// test.cpp
//
// Test runner for custom predicate implementations.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Boost /I %CPP_WORKSPACE%\_Deps\Catch2 test.cpp

// comment / uncomment to toggle implementation
// #define TEST_BOOST_IMPL

#ifdef TEST_BOOST_IMPL
#include "boost_impl.hpp"
#else
#include "stdlib_impl.hpp"
#endif 

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>
#include <functional>

TEST_CASE("equals() predicate exhibits desired semantics with std::string")
{   
    using container_t = std::string;
    auto cmp = equals<std::equal_to<typename container_t::value_type>>{};

    SECTION("equal ranges of equal length")
    {
        auto s1 = container_t{"hello"};
        auto s2 = s1;

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("unequal ranges of equal length")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{"world"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("unequal ranges of different length")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{"wor"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));   
    }

    SECTION("unequal ranges with first range empty")
    {
        auto s1 = container_t{""};
        auto s2 = container_t{"world"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("unequal ranges with second range empty")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{""};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("equal ranges with both ranges empty")
    {
        auto s1 = container_t{""};
        auto s2 = container_t{""};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }
}

TEST_CASE("equals() predicate exhibits desired semantics with std::wstring")
{   
    using container_t = std::wstring;
    auto cmp = equals<std::equal_to<typename container_t::value_type>>{};

    SECTION("equal ranges of equal length")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = s1;

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("unequal ranges of equal length")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L"world"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("unequal ranges of different length")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L"wor"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));   
    }

    SECTION("unequal ranges with first range empty")
    {
        auto s1 = container_t{L""};
        auto s2 = container_t{L"world"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("unequal ranges with second range empty")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L""};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("equal ranges with both ranges empty")
    {
        auto s1 = container_t{L""};
        auto s2 = container_t{L""};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }
}

TEST_CASE("contains() predicate exhibits desired semantics with std::string")
{
    using container_t = std::string;
    auto cmp = contains<std::equal_to<container_t::value_type>>{};

    SECTION("target contains test, test shorter than target")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{"hell"};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target does not contain test, test shorter than target")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{"help"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target contains test, test and target same length")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{"hello"};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target does not contain test, test and target same length")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{"jello"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target matches test for range, test longer than target")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{"helloworld"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target does not match test for range, test longer than target")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{"worldhello"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("test empty")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{""};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target empty")
    {
        auto s1 = container_t{""};
        auto s2 = container_t{"hello"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target and test empty")
    {
        auto s1 = container_t{""};
        auto s2 = container_t{""};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }
}

TEST_CASE("contains() predicate exhibits desired semantics with std::wstring")
{
    using container_t = std::wstring;
    auto cmp = contains<std::equal_to<container_t::value_type>>{};

    SECTION("target contains test, test shorter than target")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L"hell"};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target does not contain test, test shorter than target")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L"help"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target contains test, test and target same length")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L"hello"};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target does not contain test, test and target same length")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L"jello"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target matches test for range, test longer than target")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L"helloworld"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target does not match test for range, test longer than target")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L"worldhello"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("test empty")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L""};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target empty")
    {
        auto s1 = container_t{L""};
        auto s2 = container_t{L"hello"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target and test empty")
    {
        auto s1 = container_t{L""};
        auto s2 = container_t{L""};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }
}

TEST_CASE("starts_with() predicate exhibits desired semantics with std::string")
{
    using container_t = std::string;
    auto cmp = starts_with<std::equal_to<typename container_t::value_type>>{};

    SECTION("target starts with test, test shorter than target")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{"hell"};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target does not start with test, test shorter than target")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{"help"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target starts with test, test and target same length")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{"hello"};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target does not start with test, test and target same length")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{"hellp"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target starts with test, test longer than target")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{"helloworld"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target does not start with test, test longer than target")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{"hellpworld"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("test empty")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{""};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target empty")
    {
        auto s1 = container_t{""};
        auto s2 = container_t{"hello"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("test and target empty")
    {
        auto s1 = container_t{""};
        auto s2 = container_t{""};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }
}

TEST_CASE("starts_with() predicate exhibits desired semantics with std::wstring")
{
    using container_t = std::wstring;
    auto cmp = starts_with<std::equal_to<typename container_t::value_type>>{};

    SECTION("target starts with test, test shorter than target")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L"hell"};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target does not start with test, test shorter than target")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L"help"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target starts with test, test and target same length")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L"hello"};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target does not start with test, test and target same length")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L"hellp"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target starts with test, test longer than target")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L"helloworld"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target does not start with test, test longer than target")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L"hellpworld"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("test empty")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L""};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target empty")
    {
        auto s1 = container_t{L""};
        auto s2 = container_t{L"hello"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("test and target empty")
    {
        auto s1 = container_t{L""};
        auto s2 = container_t{L""};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }
}

TEST_CASE("ends_with() predicate exhibits desired semantics with std::string")
{
    using container_t = std::string;
    auto cmp = ends_with<std::equal_to<typename container_t::value_type>>{};

    SECTION("target ends with test, test shorter than target")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{"llo"};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    } 

    SECTION("target does not end with test, test shorter than target")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{"llp"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target ends with test, test and target same length")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{"hello"};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }  

    SECTION("target does not end with test, test and target same length")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{"hellp"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }  

    SECTION("target ends with test, test longer than target")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{"helloworld"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }  

    SECTION("target does not end with test, test longer than target")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{"worldhello"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    } 

    SECTION("test empty")
    {
        auto s1 = container_t{"hello"};
        auto s2 = container_t{""};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    } 

    SECTION("target empty")
    {
        auto s1 = container_t{""};
        auto s2 = container_t{"hello"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    } 

    SECTION("test and target empty")
    {
        auto s1 = container_t{""};
        auto s2 = container_t{""};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    } 
}

TEST_CASE("ends_with() predicate exhibits desired semantics with std::wstring")
{
    using container_t = std::wstring;
    auto cmp = ends_with<std::equal_to<typename container_t::value_type>>{};

    SECTION("target ends with test, test shorter than target")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L"llo"};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    } 

    SECTION("target does not end with test, test shorter than target")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L"llp"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }

    SECTION("target ends with test, test and target same length")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L"hello"};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }  

    SECTION("target does not end with test, test and target same length")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L"hellp"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }  

    SECTION("target ends with test, test longer than target")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L"helloworld"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    }  

    SECTION("target does not end with test, test longer than target")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L"worldhello"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    } 

    SECTION("test empty")
    {
        auto s1 = container_t{L"hello"};
        auto s2 = container_t{L""};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    } 

    SECTION("target empty")
    {
        auto s1 = container_t{L""};
        auto s2 = container_t{L"hello"};

        REQUIRE_FALSE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    } 

    SECTION("test and target empty")
    {
        auto s1 = container_t{L""};
        auto s2 = container_t{L""};

        REQUIRE(cmp(s1.begin(), s1.end(), s2.begin(), s2.end()));
    } 
}