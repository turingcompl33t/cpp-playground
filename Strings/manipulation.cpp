// manipulation.cpp
// Demo of basic std::string manipulation methods.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 manipulation.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>

TEST_CASE("std::string supports append operations")
{
    auto str = std::string{"butt"};

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
        auto other = std::string{"erfinger"};
        str.append(other.begin(), other.end());
        REQUIRE(str == "butterfinger");
    }
}

TEST_CASE("std::string supports removal with")
{
    auto str = std::string{"therein"};

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
    auto str = std::string{"substitution"};

    SECTION("a range and a char*")
    {
        str.replace(str.begin() + 9, str.end(), "e");
        REQUIRE(str == "substitute");
    }

    SECTION("two ranges")
    {
        auto other = std::string{"innuendo"};
        str.replace(str.begin(), str.begin() + 3, 
            other.begin(), other.begin() + 2);
        REQUIRE(str == "institution");
    }

    SECTION("index/length pair and a string")
    {
        auto other = std::string{"vers"};
        str.replace(3, 6, other);
        REQUIRE(str == "subversion");
    }
}

TEST_CASE("std::string supports resize operations with")
{
    auto str = std::string{"shamp"};
    
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