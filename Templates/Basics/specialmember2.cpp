// specialmember2.cpp
// Using function templates with special member functions.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 specialmember2.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>
#include <utility>
#include <type_traits>

enum class overload
{
    string_generic,
    person_copy,
    person_move
};

// a basic concept
template <typename T>
using EnableIfString = std::enable_if_t<std::is_convertible_v<T, std::string>>;

class Person
{
    std::string m_name;
    overload    m_overload;

public:
    // constructor for passed initial name
    // only enabled if argument is convertible to std::string
    template <typename Str,
              typename = EnableIfString<Str>>
    explicit Person(Str&& n) 
        : m_name{std::forward<Str>(n)}, m_overload{overload::string_generic}
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

        REQUIRE(p.ov() == overload::string_generic);
    }

    SECTION("initialization from temporary string object")
    {
        auto p = Person{"name"};

        REQUIRE(p.ov() == overload::string_generic);
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
}