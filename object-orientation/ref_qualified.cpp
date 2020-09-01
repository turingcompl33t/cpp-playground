// ref_qualified.cpp
// Demonstration of ref-qualified member functions.

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <tuple>
#include <utility>

enum class MemberType
{
    LValueQualified,
    RValueQUalified
};

class SomeObject
{
public:
    SomeObject()  = default;
    ~SomeObject() = default;

    SomeObject(SomeObject const&)            = delete;
    SomeObject& operator=(SomeObject const&) = delete;

    SomeObject(SomeObject&&)            = default;
    SomeObject& operator=(SomeObject&&) = default;

    MemberType SomeMethod() & { return MemberType::LValueQualified; }
    MemberType SomeMethod() && { return MemberType::RValueQUalified; }
};

SomeObject make_some_object()
{
    return SomeObject{};
}

TEST_CASE("the lvalue ref-qualified method is invoked")
{
    SomeObject o{};
    auto const member_type = o.SomeMethod();

    REQUIRE(member_type == MemberType::LValueQualified);
}

TEST_CASE("the rvalue ref-qualified method is invoked")
{
    SECTION("with return from factory function")
    {
        SomeObject o{};
        auto const member_type = make_some_object().SomeMethod();

        REQUIRE(member_type == MemberType::RValueQUalified);
    }

    SECTION("with explicit std::move")
    {
        SomeObject o{};
        auto const member_type = std::move(o).SomeMethod();

        REQUIRE(member_type == MemberType::RValueQUalified);
    }
}