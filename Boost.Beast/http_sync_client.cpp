// http_sync_client.cpp
// The "hello world" of Boost.Beast - a simple
// synchronous http client.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\Boost http_sync_client.cpp

#define _WIN32_WINNT 0x0601
#define BOOST_ALL_NO_LIB

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <cstdlib>
#include <string>
#include <iostream>

namespace beast = boost::beast;
namespace http  = beast::http;
namespace net   = boost::asio;

using tcp = net::ip::tcp;

constexpr auto STATUS_SUCCESS_I = 0x0;
constexpr auto STATUS_FAILURE_I = 0x1;

int main(int argc, char* argv[])
{
    if (argc != 4 && argc != 5)
    {
        std::cerr <<
            "Usage: http_sync_client <host> <port> <target> [<HTTP Version: 1.0 or 1.1(default)>]\n" <<
            "Example:\n" <<\
            "   http_sync_client www.example.com 80 /\n" <<
            "   http_sync_client www.example.com 80 / 1.0\n";
        return STATUS_FAILURE_I;
    }

    try
    {
        auto const host   = argv[1];
        auto const port   = argv[2];
        auto const target = argv[3];
        int version = (argc == 5) && !std::strcmp("1.0", argv[4]) ? 10 : 11;

        // spin up an io context
        auto ioc = net::io_context{};

        // objects to perform IO
        auto resolver = tcp::resolver{ioc};
        auto stream = beast::tcp_stream{ioc};

        // lookup the domain name
        auto const results = resolver.resolve(host, port);

        // make the connection on the resolved address
        stream.connect(results);

        // setup an HTTP GET request
        auto req = http::request<http::string_body>{http::verb::get, target, version};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // send the request synchronously
        http::write(stream, req);

        // construct a new buffer to read the response
        auto buffer = beast::flat_buffer{};
        auto res = http::response<http::dynamic_body>{};

        // read the response
        http::read(stream, buffer, res);

        // write the response to stdout
        std::cout << res << std::endl;

        // gracefully close the socket
        auto ec = beast::error_code{};
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        if (ec && ec != beast::errc::not_connected)
        {
            throw beast::system_error{ec};
        }
    }
    catch(std::exception const& e)
    {
        std::cerr << e.what() << '\n';
        return STATUS_FAILURE_I;
    }

    return STATUS_SUCCESS_I;
}