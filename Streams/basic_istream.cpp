// basic_istream.cpp
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 basic_istream.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <istream>
#include <sstream>

TEST_CASE("std::basic_istream<char>")
{
    // same as std::istream
    using stream_t = std::basic_istream<char>;

    auto b = std::stringbuf{};
    auto s = stream_t{&b};

    REQUIRE(s.good());
    REQUIRE(s.tellg() == 0);

    // replace the string buffer's underlying string
    b.str("hello");

    // extract the stream's content to a string
    auto out = std::string{};
    s >> out;

    REQUIRE(out == "hello");
}

TEST_CASE("std::basic_istream<wchar_t>")
{
    // same as std::wistream
    using stream_t = std::basic_istream<wchar_t>;

    auto b = std::wstringbuf{};
    auto s = stream_t{&b};

    REQUIRE(s.good());
    REQUIRE(s.tellg() == 0);

    // replace the string buffer's underlying string
    b.str(L"hello");

    // extract the stream's content to a string
    auto out = std::wstring{};
    s >> out;

    REQUIRE(out == L"hello");
}