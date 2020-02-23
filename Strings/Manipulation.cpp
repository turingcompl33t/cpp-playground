// Manipulation.cpp
// Demo of basic string manipulation methods.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Catch2 Manipulation.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>

TEST_CASE("std::string supports append operations")
{
    std::string str{"butt"};

    SECTION("push_back()")
    {
        str.push_back('e');
        REQUIRE(str == "butte");
    }

    SECTION("operator+=")
    {
        str += 'e';
        REQUIRE(str == "butte");
    }

    SECTION("append char")
    {
        str.append(1, 'e');
        REQUIRE(str == "butte");
    }

    SECTION("append char*")
    {
        str.append("erfinger");
        REQUIRE(str == "butterfinger");
    }

    SECTION("append half-open range")
    {
        std::string other{"erfinger"};
        str.append(other.begin(), other.end());
        REQUIRE(str == "butterfinger");
    }
}

TEST_CASE("std::string supports removal with")
{
    std::string str{"therein"};

    SECTION("pop_back()")
    {
        str.pop_back();
        str.pop_back();
        REQUIRE(str == "there");
    }

    SECTION("clear()")
    {
        str.clear();
        REQUIRE(str.empty());
    }

    SECTION("erase with half-open range")
    {
        str.erase(str.begin(), str.begin() + 3);
        REQUIRE(str == "rein");
    }

    SECTION("erase with index and length")
    {
        str.erase(5, 2);
        REQUIRE(str == "there");
    }
}

TEST_CASE("std::string supports replacement with")
{
    std::string str{"substitution"};

    SECTION("a range and a char*")
    {
        str.replace(str.begin() + 9, str.end(), "e");
        REQUIRE(str == "substitute");
    }

    SECTION("two ranges")
    {
        std::string other{"innuendo"};
        str.replace(str.begin(), str.begin() + 3, 
            other.begin(), other.begin() + 2);
        REQUIRE(str == "institution");
    }

    SECTION("index/length pair and a string")
    {
        std::string other{"vers"};
        str.replace(3, 6, other);
        REQUIRE(str == "subversion");
    }
}

TEST_CASE("std::string supports resize operations with")
{
    std::string str{"shamp"};
    
    SECTION("element removal")
    {
        str.resize(4);
        REQUIRE(str == "sham");
    }

    SECTION("element addition")
    {
        str.resize(7, 'o');
        REQUIRE(str == "shampoo");
    }
}