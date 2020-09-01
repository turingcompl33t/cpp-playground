// inheritance.cpp

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

class Base
{
protected:
    // protected members
    int m_x;
    int m_y;

public:
    Base(int const x, int const y)
        : m_x{x}, m_y{y} {}

    virtual ~Base() {}
};

class Derived : public  Base
{
public:
    Derived(int const x, int const y) 
        : Base{x, y} {}

    virtual ~Derived() override {}

    int get_x() const
    {
        return m_x;
    }

    int get_y() const
    {   
        return m_y;
    }
};

TEST_CASE("derived class can access protected data members of base")
{
    auto d = Derived{1, 2};

    REQUIRE(d.get_x() == 1);
    REQUIRE(d.get_y() == 2);
}