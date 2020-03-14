// scoped_ptr.cpp
// Demonstration of boost::scoped_ptr semantics.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++17 /I C:\Dev\Catch2 /I C:\Dev\Boost scoped_ptr.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <boost/scoped_ptr.hpp>

struct X
{
    X(unsigned long id) : m_id{id}
    {
        ++count;
    }

    ~X()
    {
        --count;
    }

    unsigned long get_id() const noexcept
    {
        return m_id;
    }

    unsigned long        m_id;
    static unsigned long count;
};

unsigned long X::count{0};

TEST_CASE("boost::scoped_ptr evaluates to")
{
    using scoped_x = boost::scoped_ptr<X>;

    SECTION("true when it owns an object")
    {
        auto ptr = scoped_x{new X{1337}};

        REQUIRE(ptr);
        REQUIRE(ptr->get_id() == 1337);
    }

    SECTION("false when it does not own an object")
    {
        auto ptr = scoped_x{nullptr};

        REQUIRE_FALSE(ptr);
    }
}

TEST_CASE("boost::scoped_ptr is an RAII wrapper")
{
    using scoped_x = boost::scoped_ptr<X>;

    REQUIRE(X::count == 0);

    auto p1 = scoped_x{new X{1337}};
    REQUIRE(X::count == 1);

    {
        auto p2 = scoped_x{new X{1054}};
        REQUIRE(X::count == 2);
    }

    REQUIRE(X::count == 1);
}

TEST_CASE("boost::scoped_ptr supports semantics like")
{
    using scoped_x = boost::scoped_ptr<X>;

    auto ptr =  scoped_x{new X{1337}};

    SECTION("operator*")
    {
        REQUIRE((*ptr).get_id() == 1337);
    }

    SECTION("opeartor->")
    {
        REQUIRE(ptr->get_id() == 1337);
    }

    SECTION("get(), which returns raw pointer")
    {
        REQUIRE_FALSE(ptr.get() == nullptr);
    }
}

TEST_CASE("boost::scoped_ptr supports comparison with nullptr")
{
    using scoped_x = boost::scoped_ptr<X>;

    SECTION("operator==")
    {
        auto ptr = scoped_x{nullptr};
        REQUIRE(ptr == nullptr);
    }

    SECTION("operator!=")
    {
        auto ptr = scoped_x{new X{1337}};
        REQUIRE(ptr != nullptr);
    }
}

TEST_CASE("boost::scoped_ptr supports swap operations")
{
    using scoped_x = boost::scoped_ptr<X>;

    auto ptr1 = scoped_x{new X{1337}};
    auto ptr2 = scoped_x{new X{1054}};

    ptr1.swap(ptr2);

    REQUIRE(ptr1->get_id() == 1054);
    REQUIRE(ptr2->get_id() == 1337);
}

TEST_CASE("boost::scoped_ptr supports reset which")
{
    using scoped_x = boost::scoped_ptr<X>;

    auto ptr = scoped_x{new X{1337}};

    SECTION("destructs the owned object")
    {
        ptr.reset();
        REQUIRE(X::count == 0);
    }

    SECTION("can replace an owned object")
    {
        auto unowned_x = new X{1054};

        REQUIRE(X::count == 2);

        ptr.reset(unowned_x);

        REQUIRE(X::count == 1);
        REQUIRE(ptr->get_id() == 1054);
        REQUIRE(ptr.get() == unowned_x);
    }
}

