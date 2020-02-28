// SequentiallyConsistent.cpp
// Examining sequentially consistent memory ordering semantics.
//
// Build
//  cl /EHsc /nologo /W4 /std:c++17 SequentiallyConsistent.cpp

#include <atomic>
#include <thread>
#include <assert.h>

static std::atomic_bool x;
static std::atomic_bool y;
static std::atomic_int  z;

void write_x()
{
    // equivalent to x.store(true)
    x.store(true, std::memory_order_seq_cst);
}

void write_y()
{
    // equivalent to y.store(true)
    y.store(true, std::memory_order_seq_cst);
}

void read_x_then_y()
{
    while (!x.load(std::memory_order_seq_cst));
    if (y.load(std::memory_order_seq_cst))
    {
        z++;
    }
}

void read_y_then_x()
{
    while (!y.load(std::memory_order_seq_cst));
    if (x.load(std::memory_order_seq_cst))
    {
        z++;
    }
}

void main()
{
    x = false;
    y = false;
    z = 0;

    std::thread a{write_x};
    std::thread b{write_y};
    std::thread c{read_x_then_y};
    std::thread d{read_y_then_x};

    a.join();
    b.join();
    c.join();
    d.join();

    // big takeaway: this assert can NEVER fire
    assert(z.load() != 0);
}