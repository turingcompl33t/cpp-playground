// manipulators.cpp
// Demo of defining custom stream manipulators.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 manipulators.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <ostream>
#include <istream>
#include <sstream>

std::ostream& exclaimer(std::ostream& stream)
{
    stream << "!";
    return stream;
}

class ignore_n
{
    int m_count;
public:
    explicit ignore_n(int count) : m_count{ count }
    {}

    template <typename char_t, typename traits>
    friend std::basic_istream<char_t, traits>&
    operator>>(std::basic_istream<char_t, traits>& stream, ignore_n& i)
    {
        stream.ignore(i.m_count);
        return stream;
    }
};

TEST_CASE("providing a custom manipultor for output stream")
{
    SECTION("without manipulator")
    {
        auto s = std::ostringstream{};
        s << "hello" << " world";
        REQUIRE(s.str() == "hello world");
    }

    SECTION("with manipulator")
    {
        auto s = std::ostringstream{};
        s << "hello" << exclaimer << " world" << exclaimer;
        REQUIRE(s.str() == "hello! world!");
    }
}

TEST_CASE("providing a custom manipulator for input stream")
{
    SECTION("without manipulator")
    {
        auto s = std::istringstream{"hello world"};
        auto c = std::string{};

        s >> c;
        REQUIRE(c == "hello");
    }

    SECTION("with manipulator")
    {
        auto s = std::istringstream{"hello world"};
        auto c = std::string{};

        auto i = ignore_n{6};

        s >> i >> c;
        REQUIRE(c == "world");
    }
}