// test.cpp

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "thread_pool_local.hpp"

constexpr static auto const N_WORK_ITEMS = 100ul;

TEST_CASE("threadpool with local work queues processes submitted work")
{
	// construct pool with only a single worker thread
	thread_pool_local pool{1};

	// need not be atomic because only a single thread will modify
	std::size_t count{};

	for (auto i = 0ul; i < 100; ++i)
	{
		pool.submit([&count](){ ++count; });
	}

	// wait for all of the work to complete
	pool.shutdown();

	REQUIRE(count == N_WORK_ITEMS);
}
