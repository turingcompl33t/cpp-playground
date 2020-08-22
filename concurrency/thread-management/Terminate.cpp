// Terminate.cpp
// Demonstration of the consequences of the destructor for a joinable 
// thread object being called.

#include <thread>
#include <iostream>

int main()
{
	using namespace std::chrono_literals;

	std::thread t{
		[]()
		{
			std::this_thread::sleep_for(5s);
		} 
	};

	// fail to join...
}