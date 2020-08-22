// unique_ptr.cpp
// Demonstration of std::unique_ptr semantics.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++17 /I %CPP_WORKSPACE%\_Deps\Catch2 unique_ptr.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <memory>

class X
{
    int m_id;

public:
    X(int id) : m_id{ id }
    {
        ++count;
    }

    ~X() 
    { 
        --count; 
    }

    int get_id() const noexcept
    {
        return m_id;
    }

    static int count;
};

int X::count = 0;

TEST_CASE("std::unique_ptr supports exclusive, transferrable ownership semantics")
{
    auto p1 = std::unique_ptr<X>{new X{1337}};
    REQUIRE(X::count == 1);

    SECTION("with move construction")
    {
        auto p2 = std::unique_ptr<X>{std::move(p1)};
        REQUIRE(X::count == 1);
        REQUIRE(p2->get_id() == 1337);
    }

    SECTION("with move assignment")
    {
        auto p2 = std::unique_ptr<X>{new X{1054}};
        
        REQUIRE(X::count == 2);

        p2 = std::move(p1);

        REQUIRE(X::count == 1);
        REQUIRE(p2->get_id() == 1337);
    }
}

TEST_CASE("std::make_unique() provides convenient construction of std::unique_ptr")
{
    REQUIRE(X::count == 0);

    {
        auto p = std::make_unique<X>(1337);

        REQUIRE(X::count == 1);
        REQUIRE(p->get_id() == 1337);
    }

    REQUIRE(X::count == 0);
}

TEST_CASE("std::unique_ptr supports other member functions")
{
    SECTION("std::unique_ptr::swap() and std::swap()")
    {
        auto p1 = std::make_unique<X>(1337);
        auto p2 = std::make_unique<X>(1054);

        REQUIRE(p1->get_id() == 1337);
        REQUIRE(p2->get_id() == 1054);

        p1.swap(p2);

        REQUIRE(p1->get_id() == 1054);
        REQUIRE(p2->get_id() == 1337);

        std::swap(p1, p2);

        REQUIRE(p1->get_id() == 1337);
        REQUIRE(p2->get_id() == 1054);
    }

    SECTION("std::unique_ptr::reset()")
    {
        auto p1 = std::make_unique<X>(1337);

        REQUIRE(static_cast<bool>(p1));

        p1.reset();

        REQUIRE_FALSE(static_cast<bool>(p1));

        auto p2 = std::make_unique<X>(1054);

        p1.reset(p2.release());

        REQUIRE_FALSE(static_cast<bool>(p2));
        REQUIRE(static_cast<bool>(p1));
        REQUIRE(p1->get_id() == 1054);
    }

    SECTION("std::unique_ptr::release()")
    {
        auto p = std::make_unique<X>(1337);

        auto raw = p.release();

        REQUIRE_FALSE(static_cast<bool>(p));
        REQUIRE(raw->get_id() == 1337);

        delete raw;
    }

    SECTION("std::unique_ptr::get()")
    {
        {
            auto p = std::make_unique<X>(1337);
            REQUIRE(X::count == 1);

            auto raw = p.get();
            REQUIRE(raw->get_id() == 1337);
        }

        // ownership maintained; destructor executed
        REQUIRE(X::count == 0);
    }
}