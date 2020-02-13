// LaunchClass.cpp
// Launch a new thread instance with a class that overrides operator().

#include <thread>
#include <iostream>

class task
{
public:
	void operator()()
	{
		std::cout << "Hello from task operator()\n";
	}
};

int main()
{
	task my_task{};
	std::thread t{ my_task };
	t.join();
}