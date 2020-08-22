// streambuf_iterators.cpp
// Demo of using input and output streambuffer iterators.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 streambuf_iterators.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <sstream>
#include <streambuf>
#include <algorithm>

TEST_CASE("output streambuffer iterators")
{
    SECTION("construction from output stream")
    {
        auto s = std::ostringstream{};

        // construct the iterator from the output stream
        auto iter = std::ostreambuf_iterator<char>{s};

        auto str = std::string{"hello world"};
        std::copy(std::begin(str), std::end(str), iter);

        REQUIRE(s.str() == "hello world");
    }

    SECTION("construction from buffer pointer")
    {
        auto s = std::ostringstream{};

        // construct from buffer pointer for stream's underlying stream buffer
        auto iter = std::ostreambuf_iterator<char>{s.rdbuf()};

        auto str = std::string{"hello world"};
        std::copy(std::begin(str), std::end(str), iter);

        REQUIRE(s.str() == "hello world");
    }
}

TEST_CASE("input streambuffer iterators")
{
    SECTION("construction from input stream")
    {
        auto s = std::istringstream{"hello world"};

        auto str = std::string{};
        std::copy(
            std::istreambuf_iterator<char>{s}, 
            std::istreambuf_iterator<char>{}, // end of stream iterator
            std::back_inserter(str)
            );

        REQUIRE(str == "hello world");
    }

    SECTION("construction from buffer pointer")
    {
        auto s = std::istringstream{"hello world"};

        auto str = std::string{};
        std::copy(
            std::istreambuf_iterator<char>{s.rdbuf()},
            std::istreambuf_iterator<char>{},
            std::back_inserter(str)
            );

        REQUIRE(str == "hello world");
    }
}