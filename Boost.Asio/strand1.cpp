// strand1.cpp
// Using strands to serialize operations.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 /I %CPP_WORKSPACE%\_Deps\Boost strand1.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#define BOOST_ALL_NO_LIB

#include <thread>
#include <vector>
#include <boost/asio.hpp>

namespace net = boost::asio;

constexpr auto N_THREADS    = 5;
constexpr auto N_WORK_ITEMS = 1000;

TEST_CASE("using strands to serialize async operations")
{
    auto ioc    = net::io_context{};
    auto strand = net::make_strand(ioc);

    auto count = 0ul;

    for (auto i = 0u; i < N_WORK_ITEMS; ++i)
    {
        // post in a strand to ensure this work is
        // never executed concurrently
        net::post(strand, [&count](){ ++count; });
    }

    auto threads = std::vector<std::thread>{};

    for (auto i = 0u; i < N_THREADS; ++i)
    {
        threads.emplace_back([&ioc](){ ioc.run(); });
    }

    for (auto& t : threads)
    {
        t.join();
    }

    REQUIRE(count == N_WORK_ITEMS);
}