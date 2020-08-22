// sequentially_consistent.cpp
// Examining sequentially consistent memory ordering semantics.

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <atomic>
#include <thread>

void write_x(std::atomic_bool& x)
{
    // equivalent to x.store(true)
    x.store(true, std::memory_order_seq_cst);
}

void write_y(std::atomic_bool& y)
{
    // equivalent to y.store(true)
    y.store(true, std::memory_order_seq_cst);
}

void read_x_then_y(std::atomic_bool& x, std::atomic_bool& y, std::atomic_int& z)
{
    while (!x.load(std::memory_order_seq_cst));
    if (y.load(std::memory_order_seq_cst))
    {
        z++;
    }
}

void read_y_then_x(std::atomic_bool& x, std::atomic_bool& y, std::atomic_int& z)
{
    while (!y.load(std::memory_order_seq_cst));
    if (x.load(std::memory_order_seq_cst))
    {
        z++;
    }
}

TEST_CASE("it works")
{
    std::atomic_bool x{false};
    std::atomic_bool y{false};
    std::atomic_int  z{0};

    std::thread a{write_x, std::ref(x)};
    std::thread b{write_y, std::ref(y)};
    std::thread c{read_x_then_y, std::ref(x), std::ref(y), std::ref(z)};
    std::thread d{read_y_then_x, std::ref(x), std::ref(y), std::ref(z)};

    a.join();
    b.join();
    c.join();
    d.join();

    REQUIRE(((z.load() == 1) || (z.load() == 2)));
}