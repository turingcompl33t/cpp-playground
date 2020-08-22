// thread_pool_basic_test.cpp
// Unit test for cdl::threadpool::thread_pool_basic.
//
// Build
//	cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\CDL thread_pool_basic_test.cpp

#include <chrono>
#include <iostream>

#include "cdl/synchronization/monitor.hpp"
#include "cdl/threadpool/thread_pool_basic.hpp"

constexpr auto N_WORK_ITEMS = 10;

int main()
{
	using namespace std::chrono_literals;

	cdl::synchronization::monitor<std::ostream&> sync_cout{ std::cout };

	cdl::threadpool::thread_pool_basic pool{};

	for (unsigned i = 0; i < N_WORK_ITEMS; ++i)
	{
		pool.submit([=, &sync_cout]()
			{
				sync_cout([=](std::ostream& cout) {cout << "Executing Task " << i << '\n'; });
			}
		);
	}

	// close the pool and wait on all pending tasks
	pool.shutdown();
}