// thread_pool_waitable_test.cpp
// Unit test for cdl::threadpool::thread_pool_waitable.
//
// Build
//	cl /EHsc /nologo /std:c++17 /W4 /I C:\Dev\CDL thread_pool_waitable_test.cpp

#include <iostream>

#include "cdl/synchronization/monitor.hpp"
#include "cdl/threadpool/thread_pool_waitable.hpp"

constexpr auto N_WORK_ITEMS = 10;

int main()
{
	cdl::synchronization::monitor<std::ostream&> sync_cout{ std::cout };

	cdl::threadpool::thread_pool_waitable pool{};

	for (unsigned i = 0; i < N_WORK_ITEMS; ++i)
	{
		pool.submit([=, &sync_cout]()
			{
				sync_cout([=](std::ostream& cout) {cout << "Executing Task " << i << '\n'; });
			}
		);
	}

	auto fut    = pool.submit([]() { return 17; });
	auto result = fut.get();

	sync_cout([=](std::ostream& cout) {cout << "Result = " << result << '\n'; });

	pool.shutdown();
}