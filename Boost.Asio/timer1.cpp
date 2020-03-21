// timer1.cpp
// Simple timer with boost asio.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 /I C:\Dev\Boost timer1.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#define BOOST_ALL_NO_LIB

#include <chrono>
#include <boost/asio.hpp>

namespace net = boost::asio;

TEST_CASE("basic timer example")
{
    using namespace boost::system;
    using namespace std::chrono_literals;

    auto ioc   = net::io_context{};
    auto timer = net::steady_timer{ioc};

    auto flag = bool{false};

    timer.expires_after(2s);
    timer.async_wait([&flag](error_code const&){ flag = true; });

    // give this thread to the IO context, blocks here
    // until all work is completed
    ioc.run();

    REQUIRE(flag);
}