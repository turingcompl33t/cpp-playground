// shared_from_this.cpp
// Demo of correct and incorrect methods for acquiring a 
// std::shared_ptr to oneself.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 shared_from_this.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <memory>

class correct
    : std::enable_shared_from_this<correct>
{
public:
    std::shared_ptr<correct> get_ptr()
    {
        return shared_from_this();
    }
};

class incorrect
{
public:
    std::shared_ptr<incorrect> get_ptr()
    {
        return std::shared_ptr<incorrect>{this};
    }
};

TEST_CASE("using std::enable_shared_from_this maintains proper reference counting semantics")
{
    auto c1 = std::make_shared<correct>();
    auto c2 = c1->get_ptr();

    REQUIRE(c1.use_count() == 2);
}

TEST_CASE("using std::enable_shared_from_this throws when the caller is not owned by std::shared_ptr")
{
    auto c1 = correct{};
    REQUIRE_THROWS_AS(c1.get_ptr(), std::bad_weak_ptr);
}

TEST_CASE("when std::shared_ptr is initialized from this pointer a distinct reference count is maintained")
{
    auto i1 = std::make_shared<incorrect>();
    auto i2 = i1->get_ptr();

    REQUIRE(i1.use_count() == 1);
    REQUIRE(i2.use_count() == 2);

    // double free
}