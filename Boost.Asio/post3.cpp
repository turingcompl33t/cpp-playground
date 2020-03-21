// post3.cpp
// Using a work guard to keep IO context alive without work pending.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 /I C:\Dev\Boost post3.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#define BOOST_ALL_NO_LIB

#include <thread>
#include <vector>
#include <boost/asio.hpp>

namespace net = boost::asio;

TEST_CASE("work guards prevent premature IO context exit")
{
    auto ioc = net::io_context{};

    // create a work guard for the IO context;
    // context exit now controlled by guard lifetime 
    auto guard = net::make_work_guard(ioc);

    // without the work guard, this thread would exit
    // immediately and work would never get done
    auto t = std::thread{[&ioc](){ ioc.run(); }};

    auto flag = bool{false};

    net::post(ioc, [&flag](){ flag = true; });
    
    // now that the work is posted, need to reset the work
    // guard, otherwise the IO context will continue to behave
    // as if work is outstanding, the thread will never exit
    guard.reset();

    t.join();

    REQUIRE(flag);
}