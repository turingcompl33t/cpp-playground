// post1.cpp
// Posting work directly to the system executor.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I %CPP_WORKSPACE%\_Deps\Catch2 /I %CPP_WORKSPACE%\_Deps\Boost post1.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#define BOOST_ALL_NO_LIB
#include <boost/asio.hpp>

namespace net = boost::asio;

TEST_CASE("posting a single work item to the system executor")
{
    auto ioc = net::io_context{};

    auto flag = bool{false};

    net::post(ioc, [&flag](){ flag = true; });

    ioc.run();

    REQUIRE(flag);
}