// LaunchLambda.cpp
// Launch a new thread instance with an inline lambda expression.

#include <thread>
#include <iostream>

int main()
{
	std::thread t{ 
		[]()
		{
			std::cout << "Hello from inline lambda\n";
		}
	};

	t.join();
}