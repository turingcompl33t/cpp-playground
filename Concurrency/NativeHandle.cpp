// NativeHandle.cpp
// What additional functionality is provided by native_handle?

#include <thread>
#include <iostream>

int main()
{
	std::thread t{ thread_fn };

	auto* native_handle = t.native_handle();

	return 0;
}

void thread_fn()
{
	return;
}