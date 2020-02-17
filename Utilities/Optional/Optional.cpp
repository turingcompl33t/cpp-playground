// Optional.cpp
// Demo of std::optional.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I c:\Dev\Boost /I c:\Dev\Catch2 Optional.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <optional>

struct SomeObject
{
    SomeObject(int p) : property_{p}
    {}
    int const property_;
};

enum class Selector { Yes, No };

std::optional<SomeObject> make_object(Selector select)
{
    if (select == Selector::Yes)
    {
        return SomeObject{16};
    }
    return std::nullopt;
}

TEST_CASE("std::optional contains types")
{
    auto object_opt = make_object(Selector::Yes);
    if (object_opt)
    {
        REQUIRE(object_opt->property_ == 16);
        auto& object = object_opt.value();
        REQUIRE(object.property_ == 16);
    }
    else
    {
        FAIL("optional value evaluated to false");
    }
}

TEST_CASE("std::optional can be empty")
{
    auto object_opt = make_object(Selector::No);
    if (object_opt)
    {
        FAIL("the object is not empty");
    }

    REQUIRE_FALSE(object_opt.has_value());
}

TEST_CASE("std::optional supports convenience method value_or()")
{
    auto object_yes = make_object(Selector::Yes);
    auto object_no = make_object(Selector::No);

    auto opt_yes = object_yes.value_or(SomeObject{18});
    auto opt_no = object_no.value_or(SomeObject{18});

    REQUIRE(opt_yes.property_ == 16);
    REQUIRE(opt_no.property_ == 18);
}