// elements.cpp
// Demo of basic std::string element and iterator access methods.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 elements.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>

TEST_CASE("std::string::c_str() produces null-terminated string")
{
    auto str = std::string{"hello"};
    auto as_cstr = str.c_str();

    REQUIRE(as_cstr[0] == 'h');
    REQUIRE(as_cstr[1] == 'e');
    REQUIRE(as_cstr[2] == 'l');
    REQUIRE(as_cstr[3] == 'l');
    REQUIRE(as_cstr[4] == 'o');
    REQUIRE(as_cstr[5] == '\0');
}

TEST_CASE("std::string supports iteration")
{
    auto str = std::string{"hello world"};

    auto iter1 = str.begin();
    auto iter2 = str.end();

    REQUIRE(*iter1 == 'h');
    ++iter1;
    REQUIRE(*iter1 == 'e');

    --iter2;
    REQUIRE(*iter2 == 'd');
    --iter2;
    REQUIRE(*iter2 == 'l');
}

TEST_CASE("std::string iterator supports writes")
{
    auto str = std::string{"hello"};

    REQUIRE(str == "hello");
    str.front() = 'j';
    REQUIRE(str == "jello");
    str.back() = 'y';
    REQUIRE(str == "jelly");
}