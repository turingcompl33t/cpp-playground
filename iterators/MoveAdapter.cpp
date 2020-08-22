// MoveAdapter.cpp
// Demo of basic move iterator adapter usage.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 MoveAdapter.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <iterator>

#include <vector>

struct Moveable
{
    Moveable(int i) : i_{i} {}
    Moveable(Moveable&& m)
    {
        i_ = m.i_;
        m.i_ = 0;
    }

    int i_;
};

TEST_CASE("move iterators convert assignment into move operations")
{
    std::vector<Moveable> donor{};
    donor.emplace_back(1);
    donor.emplace_back(2);
    donor.emplace_back(3);
    
    std::vector<Moveable> recipient{
        std::make_move_iterator(donor.begin()),
        std::make_move_iterator(donor.end())
    };

    // all elements of donor in moved-from state
    REQUIRE(donor[0].i_ == 0);
    REQUIRE(donor[1].i_ == 0);
    REQUIRE(donor[2].i_ == 0);

    // all elements of recipient successfully move constructed
    REQUIRE(recipient[0].i_ == 1);
    REQUIRE(recipient[1].i_ == 2);
    REQUIRE(recipient[2].i_ == 3);
}