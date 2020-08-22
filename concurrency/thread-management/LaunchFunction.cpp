// LaunchFunction.cpp
// Launch a new thread instance with a free function.

#include <thread>
#include <iostream>

void task()
{
	std::cout << "Hello from task()\n";
}

int main()
{
	std::thread t{ task };
	t.join();
}