// threadpool.cpp
//
// Trying out ASIO's threadpool type.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 /I %CPP_WORKSPACE%\_Deps\Boost threadpool.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#define BOOST_ALL_NO_LIB
#include <atomic>
#include <boost/asio.hpp>

namespace net = boost::asio;

TEST_CASE("boost::asio::thread_pool supports asynchronous work")
{
    auto pool = net::thread_pool{};

    auto count = std::atomic_ulong{};

    for (auto i = 0u; i < 10; ++i)
    {
        net::post(pool, [&c = count]{ ++c; });
    }

    pool.join();

    REQUIRE(count == 10);
}