// post2.cpp
// Posting work directly to the system executor.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 /I %CPP_WORKSPACE%\_Deps\Boost post2.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#define BOOST_ALL_NO_LIB
#include <thread>
#include <boost/asio.hpp>

namespace net = boost::asio;

TEST_CASE("posting multiple work items to the system executor")
{
    auto ioc = net::io_context{};

    auto f1 = bool{false};
    auto f2 = bool{false};

    net::post(ioc, [&f1](){ f1 = true; });
    net::post(ioc, [&f2](){ f2 = true; });

    // give a single thread to the executor to execute our work
    auto t = std::thread{[&ioc](){ ioc.run(); }};
    t.join();

    REQUIRE((f1 && f2));
}