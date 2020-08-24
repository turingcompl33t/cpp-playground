// guarantees.cpp
// 
// A look at the four levels of exception safety guarantees.
//
// WARNING: extremely contrived example with poor class design.

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <stdexcept>

class SomeType
{
    int m_val1;
    int m_val2;
    int m_sum;
public:
    SomeType(int v1, int v2) 
        : m_val1{v1}, m_val2{v2}, m_sum{v1+v2}
    {}

    void swap(SomeType& other) noexcept
    {
        std::swap(m_val1, other.m_val1);
        std::swap(m_val2, other.m_val2);
        std::swap(m_sum, other.m_sum);
    }

    void recompute() noexcept
    {
        m_sum = m_val1 + m_val2;
    }

    int& get_val1()
    {
        return m_val1;
    }

    int& get_val2()
    {
        return m_val2;
    }

    void set(int v1, int v2) noexcept
    {
        m_val1 = v1;
        m_val2 = v2;
        m_sum = v1 + v2;
    }

    bool invariants_maintained() const noexcept
    {
        return m_sum == (m_val1 + m_val2);
    }

    bool operator==(SomeType const& other) const noexcept
    {
        return m_val1 == other.m_val1 
            && m_val2 == other.m_val2 
            && m_sum == other.m_sum;
    }
};

int non_throwing_computation()
{
    return 10;
}

int throwing_computation()
{
    throw std::logic_error{"Computation Failed!"};
    return 15;
}

void unsafe_update(SomeType& t)
{
    t.get_val1() = non_throwing_computation();
    t.get_val2() = throwing_computation();

    t.recompute();
}

void basic_update(SomeType& t)
{
    auto tmp1 = non_throwing_computation();
    auto tmp2 = non_throwing_computation();

    // does not throw
    t.set(tmp1, tmp2);

    // but then we do more work that throws...
    throwing_computation();
}

void strong_update(SomeType& t)
{
    auto tmp1 = non_throwing_computation();
    auto tmp2 = throwing_computation();

    // do anything else that might throw

    // does not throw
    t.set(tmp1, tmp2);
}

void nothrow_update(SomeType& t) noexcept
{
    auto tmp1 = non_throwing_computation();
    auto tmp2 = non_throwing_computation();

    t.set(tmp1, tmp2);
}

TEST_CASE("no guarantee")
{
    auto t = SomeType{2, 4};
    
    // the update operation throws
    REQUIRE_THROWS_AS(unsafe_update(t), std::logic_error);

    // and the object invariants are no maintained
    REQUIRE_FALSE(t.invariants_maintained());
}

TEST_CASE("the basic exception safety guarantee")
{
    auto t = SomeType{2, 4};

    // the update operation throws
    REQUIRE_THROWS_AS(basic_update(t), std::logic_error);
    
    // the invariants of the object are maintained
    REQUIRE(t.invariants_maintained());

    // but the object state has been altered
    REQUIRE_FALSE(t == SomeType{2, 4});
}

TEST_CASE("the strong exception safety guarantee")
{
    auto t = SomeType{2, 4};

    // the update operation throws
    REQUIRE_THROWS_AS(strong_update(t), std::logic_error);

    // the invariants of the object are maintained
    REQUIRE(t.invariants_maintained());

    // and the object state is unaltered
    REQUIRE(t == SomeType{2, 4});
}

TEST_CASE("the nothrow or nofail guarantee")
{
    auto t = SomeType{2, 4};

    // the update does not throw
    REQUIRE_NOTHROW(nothrow_update(t));
}