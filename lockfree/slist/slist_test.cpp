// slist_test.cpp
// Unit Test: cdl::lockfree::slist
//
// Build
//	cl /EHsc /nologo /std:c++17 /W4 slist_test.cpp

#include <vector>
#include <thread>
#include <iostream>

#include "slist.hpp"

constexpr static auto const SUCCESS = 0x0;
constexpr static auto const FAILURE = 0x1;

constexpr auto N_THREADS   = 10;
constexpr auto N_ITEMS     = 1000;

slist<unsigned> g_list{};

void producer(unsigned id)
{
    for (auto i = 0; i < N_ITEMS; ++i)
    {
        g_list.push_front(id);
    }
}

void consumer()
{
    for (auto i = 0; i < N_ITEMS; ++i)
    {
        g_list.pop_front();
    }
}

int main()
{
    std::vector<std::thread> threads{};

    for (auto i = 0; i < N_THREADS; ++i)
    {
        threads.emplace_back(producer, i);
        threads.emplace_back(consumer);
    }

    for (auto& t : threads)
    {
        t.join();
    }

    return SUCCESS;
}