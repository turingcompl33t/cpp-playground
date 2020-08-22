// overload_extractor.cpp
// Demonstration of basic operator>> overloading.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 overload_extractor.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>
#include <sstream>

class consumer
{
    std::string m_str;
public:
    friend std::istream& operator>>(std::istream& stream, consumer& c)
    {
        stream >> c.m_str;
        return stream;
    }

    std::string const& str() const noexcept
    {
        return m_str;
    }
};

TEST_CASE("overloading operator>> for a custom type")
{
    auto s = std::istringstream{"hello"};
    auto c = consumer{};

    // extract the string from the stringstream
    s >> c;

    REQUIRE(c.str() == "hello");
}