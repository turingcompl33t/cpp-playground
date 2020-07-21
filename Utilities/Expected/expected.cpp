// expected.cpp
//
// Build
//  gcc -Wall -Werror -std=c++2a -I${CPP_WORKSPACE}/_Deps/expected/include expected.cpp -o expected.out

#include <cassert>
#include <system_error>

#include <tl/expected.hpp>

static tl::expected<int, std::errc> test_fn(bool success)
{
    if (success)
    {
        return 1337;
    }
    else
    {
        return tl::unexpected(std::errc::bad_file_descriptor);
    }
}

int main()
{
    auto const e1 = test_fn(true);
    auto const e2 = test_fn(false);

    assert(e1.has_value());
    assert(!e2.has_value());
}