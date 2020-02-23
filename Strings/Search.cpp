// Search.cpp
// Demo of basic string search operations.
// 
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Catch2 Search.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>

TEST_CASE("std::string find")
{
    using namespace std::string_literals;
    
    std::string word{"pizzazz"};

    SECTION("locates substrings from strings")
    {
        REQUIRE(word.find("zz"s) == 2);  // pi(z)zazz
    }

    SECTION("accepts a position argument")
    {
        REQUIRE(word.find("zz"s, 3) == 5);  // pizza(z)z
    }

    SECTION("locates substrings from char*")
    {
        REQUIRE(word.find("zaz") == 3);  // piz(z)azz
    }

    SECTION("returns npos when not found")
    {
        REQUIRE(word.find('x') == std::string::npos);
    }
}

TEST_CASE("std::string rfind")
{
    using namespace std::string_literals;
    
    std::string word{"pizzazz"};

    SECTION("locates substrings from strings")
    {
        REQUIRE(word.rfind("zz"s) == 5);  // pizza(z)z
    }

    SECTION("accepts a position argument")
    {
        REQUIRE(word.rfind("zz"s, 4) == 2);  // pizza(z)z
    }

    SECTION("locates substrings from char*")
    {
        REQUIRE(word.rfind("zaz") == 3);  // piz(z)azz
    }

    SECTION("returns npos when not found")
    {
        REQUIRE(word.find('x') == std::string::npos);
    }
}

TEST_CASE("std::string::find_first_of()")
{
    using namespace std::string_literals;

    std::string word{"pizzazz"};

    SECTION("locates characters within another string")
    {
        REQUIRE(word.find_first_of("zz"s) == 2);  // pi(z)zazz
    }

    SECTION("returns npos when not found")
    {
        REQUIRE(word.find_first_of("xx"s) == std::string::npos);
    }
}

TEST_CASE("std::string::find_last_of()")
{
    using namespace std::string_literals;

    std::string word{"pizzazz"};

    SECTION("locates characters within another string")
    {
        REQUIRE(word.find_last_of("zz"s) == 6);  // pizzaz(z)
    }

    SECTION("returns npos when not found")
    {
        REQUIRE(word.find_last_of("xx"s) == std::string::npos);
    }
}