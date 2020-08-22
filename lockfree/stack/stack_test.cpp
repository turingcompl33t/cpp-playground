// stack_test.cpp
//
// Build
//	cl /EHsc /nologo /std:c++17 /W4 stack_test.cpp

#include <thread>
#include <vector>
#include <cstdio>

#include "stack.hpp"

constexpr static auto const SUCCESS = 0x0;
constexpr static auto const FAILURE = 0x1;

constexpr auto N_PRODUCERS = 10;
constexpr auto N_CONSUMERS = 10;

stack<int> work_stack{};

void producer_fn(int index)
{
	work_stack.push(index);
	printf("Pushed: %d\n", index);
}

void consumer_fn()
{
	auto item = work_stack.pop();
	printf("Popped: %d\n", *item);
}

int main()
{
	auto threads = std::vector<std::thread>{};

	for (int i = 0; i < N_PRODUCERS; ++i)
	{
		threads.emplace_back(producer_fn, i);
	}

	for (int i = 0; i < N_CONSUMERS; ++i)
	{
		threads.emplace_back(consumer_fn);
	}

	// join on all threads
	for (auto& t : threads)
	{
		t.join();
	}

	return SUCCESS;
}