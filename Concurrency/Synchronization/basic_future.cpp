// basic_future.cpp
// Demonstration of basic future usage.

#include <future>
#include <iostream>

constexpr static auto const SUCCESS = 0x0;
constexpr static auto const FAILURE = 0x1;

int main()
{
	auto fut = std::async(std::launch::async, [] {
		std::cout << "Hello from async task\n";
		}
	);

	fut.wait();
	return SUCCESS;
}