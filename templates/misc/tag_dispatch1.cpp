// tag_dispatch1.cpp
//
// Simple example of tag dispatch to modify behavior.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 tag_dispatch1.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

enum class constructed_with
{
    tag_1,
    tag_2
};

class dispatchable
{
    constructed_with m_constructed_with;

public:
    struct tag_1 {};
    struct tag_2 {};

    dispatchable(tag_1) : m_constructed_with{ constructed_with::tag_1 }
    {}

    dispatchable(tag_2) : m_constructed_with{ constructed_with::tag_2 }
    {}

    constructed_with query() const noexcept
    {
        return m_constructed_with;
    }
};

TEST_CASE("tag dispatch allows selection between class constructors that accept no data arguments")
{
    auto d1 = dispatchable{dispatchable::tag_1()};
    auto d2 = dispatchable{dispatchable::tag_2()};

    REQUIRE(d1.query() == constructed_with::tag_1);
    REQUIRE(d2.query() == constructed_with::tag_2);
}