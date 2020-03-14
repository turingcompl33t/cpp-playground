// weak_ptr.cpp
// Demonstration of std::weak_ptr semantics.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++17 /I C:\Dev\Catch2 weak_ptr.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <memory>

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

TEST_CASE("std::weak_ptr lock() yields")
{
    SECTION("std::shared_ptr when tracked object is valid")
    {
        auto shared = std::make_shared<X>(1337);

        auto weak = std::weak_ptr<X>{shared};
        auto locked = weak.lock();

        REQUIRE(locked->get_id() == 1337);

        REQUIRE(X::count == 1);            // only a single object exists
        REQUIRE(locked.use_count() == 2);  // 2 shared pointers currently track it
    }

    SECTION("empty when tracked object is invalid")
    {
        auto weak = std::weak_ptr<X>{};
        {
            auto shared = std::make_shared<X>(1337);
            weak = shared;  // copy assign weak ptr
        }

        auto locked = weak.lock();
        REQUIRE(locked == nullptr);
        REQUIRE(weak.expired());
    }
}