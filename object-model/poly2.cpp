// poly2.cpp
//
// Overloading operators.

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <memory>
#include <vector>

class Boolean
{
public:
    virtual explicit operator bool() const = 0;
};

class True : public Boolean
{
public:
    virtual explicit operator bool() const override 
    {
        return true;
    }
};

class False : public Boolean 
{
public:
    virtual explicit operator bool() const override 
    {
        return false;
    }
};

TEST_CASE("virtual dispatch behaves as expected with operators")
{
    std::vector<std::unique_ptr<Boolean>> values{};
    values.emplace_back(new True{});
    values.emplace_back(new False{});

    REQUIRE(static_cast<bool>(*values[0].get()));
    REQUIRE_FALSE(static_cast<bool>(*values[1].get()));
}