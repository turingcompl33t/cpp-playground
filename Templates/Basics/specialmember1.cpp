// specialmember1.cpp
// Using function templates with special member functions.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 specialmember1.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>
#include <utility>

enum class overload
{
    string_copy,
    string_move,
    person_copy,
    person_move
};

class Person
{
    std::string m_name;
    overload    m_overload;

public:
    // constructor for passed initial name
    explicit Person(std::string const& n) 
        : m_name{n}, m_overload{overload::string_copy}
    {}

    // constructor for passed initial name
    explicit Person(std::string&& n) 
        : m_name{std::move(n)}, m_overload{overload::string_move}
    {}

    // copy constructor
    Person(Person const& p)
        : m_name{p.m_name}, m_overload{overload::person_copy}
    {}

    // move constructor
    Person(Person&& p)
        : m_name{std::move(p.m_name)}, m_overload{overload::person_move}
    {}

    overload ov() const noexcept
    {
        return m_overload;
    }
};

TEST_CASE("the expected constructor is invoked for")
{
    SECTION("initialization from string object")
    {
        auto s = std::string{"name"};
        
        auto p = Person{s};
        REQUIRE(p.ov() == overload::string_copy);
    }

    SECTION("initialization from temporary string object")
    {
        auto p = Person{"name"};
        REQUIRE(p.ov() == overload::string_move);
    }

    SECTION("initialization from person object")
    {
        auto src = Person{"name"};
        auto dst = Person{src};

        REQUIRE(dst.ov() == overload::person_copy);
    }

    SECTION("initialization from movable person object")
    {
        auto src = Person{"name"};
        auto dst = Person{std::move(src)};

        REQUIRE(dst.ov() == overload::person_move);
    }

    SECTION("initialization from temporary person object (string object)")
    {
        auto s = std::string{"name"};
        auto dst = Person{Person{s}};

        // TODO: why??
        REQUIRE(dst.ov() == overload::string_copy);
    }

    SECTION("initialization from temporary person object (temporary string object")
    {
        auto dst = Person{Person{"name"}};

        // TODO: why??
        REQUIRE(dst.ov() == overload::string_move);
    }
}

