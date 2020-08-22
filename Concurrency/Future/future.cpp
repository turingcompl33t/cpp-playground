// future_test.cpp
// Unit test for cdl::synchronization::future and
// cdl::synchronization::promise.
//
// Build
//  cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\CDL future_test.cpp

#include <iostream>

#include "cdl/synchronization/future.hpp"
#include "cdl/synchronization/monitor.hpp"
#include "cdl/threadpool/thread_pool_basic.hpp"

cdl::synchronization::monitor<std::ostream&> sync_cout{ std::cout };

unsigned expensive_computation(unsigned task_id)
{
    using namespace std::chrono_literals;

    sync_cout([=](std::ostream& cout){ cout << "[" << task_id << "] START\n"; });

    std::this_thread::sleep_for(3s);

    sync_cout([=](std::ostream& cout){ cout << "[" << task_id << "] STOP\n"; });

    return task_id*2;
}

int main()
{
    using cdl::synchronization::promise;
    using cdl::synchronization::future;

    // thread pool models simple user-mode scheduler
    cdl::threadpool::thread_pool_basic pool{};

    promise<unsigned> pa{};
    promise<unsigned> pb{};

    future<unsigned> fa = pa.get_future();
    future<unsigned> fb = pb.get_future();

    pool.submit([&]() {
        pa.set_value(expensive_computation(10));
    });
    pool.submit([&]() {
        pb.set_value(expensive_computation(20));
    });

    auto result = fa.get() + fb.get();

    sync_cout([=](std::ostream& cout){ cout << "Result = " << result << '\n'; });

    pool.shutdown();
}