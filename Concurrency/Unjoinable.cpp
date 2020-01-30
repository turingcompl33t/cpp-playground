// Unjoinable.cpp
// Demo of what happens when the dtor for a joinable thread is invoked.
//
// This program crashes (via call to std::terminate) because the 
// destructor for thread object t is invoked while t remains in 
// a joinable state.

#include <thread>
#include <chrono>
#include <iostream>

void thread_fn(void);

int main()
{
	std::cout << "Launching thread...\n";

	{
		// launch the thread
		std::thread t{ thread_fn };

		std::this_thread::sleep_for(std::chrono::seconds(1));

		// thread dtor called here
		std::cout << "calling thread dtor without joining / detaching...\n";
	}

	return 0;
}

void thread_fn(void)
{
	std::cout << "Thread running\n";

	for (;;)
	{
		// spin forever
	}
}