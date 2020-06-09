// optional.cpp
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 optional.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <vector>
#include <optional>

struct some_object
{
    some_object(int p) : property_{p} {}
    int const property_;
};

enum class selector { yes, no };

[[nodiscard]]
std::optional<some_object> 
make_object(selector select)
{
    
    return select == selector::yes 
        ? std::make_optional(some_object{16})
        : std::nullopt;
}

TEST_CASE("std::optional contains types")
{
    auto object_opt = make_object(selector::yes);
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
    auto object_opt = make_object(selector::no);
    if (object_opt)
    {
        FAIL("the object is not empty");
    }

    REQUIRE_FALSE(object_opt.has_value());
}

TEST_CASE("std::optional supports convenience method value_or()")
{
    auto object_yes = make_object(selector::yes);
    auto object_no = make_object(selector::no);

    auto opt_yes = object_yes.value_or(some_object{18});
    auto opt_no = object_no.value_or(some_object{18});

    REQUIRE(opt_yes.property_ == 16);
    REQUIRE(opt_no.property_ == 18);
}

[[nodiscard]]
std::optional<std::vector<int>>
make_vector()
{
    auto v = std::vector<int>{};
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);

    return v;
}

TEST_CASE("std::optional supports returning containers")
{
    auto const v_opt = make_vector();

    REQUIRE(v_opt.has_value());

    auto const& v = v_opt.value();

    REQUIRE(v[0] == 0);
    REQUIRE(v[1] == 1);
    REQUIRE(v[2] == 2);
}
