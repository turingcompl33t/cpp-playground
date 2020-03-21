// composed1.cpp
// Composing asynchronous operations.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Catch2 /I C:\Dev\Boost composed1.cpp

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#define BOOST_ALL_NO_LIB

#include <future>
#include <string>
#include <utility>
#include <cstring>
#include <type_traits>

#include <boost/asio/write.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/use_future.hpp>
#include <boost/asio/io_context.hpp>

using boost::asio::ip::tcp;

constexpr auto TEST_STR_1 = "Testing callback\r\n";
constexpr auto TEST_STR_2 = "Testing future\r\n";

// This is the simplest example of a composed asynchronous operation, where we
// simply repackage an existing operation. The asynchronous operation
// requirements are met by delegating responsibility to the underlying
// operation.

template <typename CompletionToken>
auto async_write_message(
    tcp::socket& socket,
    const char* message, 
    CompletionToken&& token
    ) -> typename boost::asio::async_result<
        std::decay_t<CompletionToken>,
        void(boost::system::error_code, std::size_t)>::return_type
{
    // When delegating to the underlying operation we must take care to perfectly
    // forward the completion token. This ensures that our operation works
    // correctly with move-only function objects as callbacks, as well as other
    // completion token types.
    return boost::asio::async_write(
        socket,
        boost::asio::buffer(message, std::strlen(message)),
        std::forward<CompletionToken>(token)
        );
}

void do_connect()
{
    auto ioc = boost::asio::io_context{};
    auto sock = tcp::socket{ioc};

    auto resolver = tcp::resolver{ioc};
    boost::asio::connect(sock, resolver.resolve("127.0.0.1", "55555"));

    // hang out
}

std::size_t test_callback()
{
    auto ioc = boost::asio::io_context{};

    auto acceptor = tcp::acceptor{ioc, {tcp::v4(), 55555}};
    auto socket = acceptor.accept();

    auto written = std::size_t{};

    // Test our asynchronous operation using a lambda as a callback.
    async_write_message(
        socket, 
        TEST_STR_1,
        [&written](const boost::system::error_code& error, std::size_t n)
        {
            written = error ? 0 : n;
        });

    ioc.run();

    return written;
}

std::size_t test_future()
{
    auto ioc = boost::asio::io_context{};

    auto acceptor = tcp::acceptor{ioc, {tcp::v4(), 55555}};
    auto socket = acceptor.accept();

    // Test our asynchronous operation using the use_future completion token.
    // This token causes the operation's initiating function to return a future,
    // which may be used to synchronously wait for the result of the operation.
    std::future<std::size_t> f = async_write_message(
        socket, 
        TEST_STR_2, 
        boost::asio::use_future
        );

    ioc.run();

    auto written = std::size_t{};

    try
    {
        // Get the result of the operation.
        written = f.get();
    }
    catch (const std::exception&)
    {
        written = 0;
    }

    return written;
}

TEST_CASE("composed async operation with callback")
{
    auto f1 = std::async(std::launch::async, test_callback);
    auto f2 = std::async(std::launch::async, do_connect);
    
    f2.wait();

    REQUIRE(f1.get() == std::strlen(TEST_STR_1));
}

TEST_CASE("composed async operation with std::future")
{
    auto f1 = std::async(std::launch::async, test_future);
    auto f2 = std::async(std::launch::async, do_connect);

    f2.wait();

    REQUIRE(f1.get() == std::strlen(TEST_STR_2));
}