// BasicFuture.cpp
// Demonstration of basic future usage.

#include <future>
#include <iostream>

int main()
{
	auto fut = std::async(std::launch::async, [] {
		std::cout << "Hello from async task\n";
		}
	);

	fut.wait();
}