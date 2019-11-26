// Thread.cpp
// Demo of C++11 low-level thread API.

#include <thread>
#include <iostream>
#include <string_view>

// milliseconds
constexpr auto SLEEP_TIME = 5000;

void ThreadFn();

void LogWithThread(const std::string_view msg);

int main()
{
    LogWithThread("Main thread: ENTER");

    std::thread t{ ThreadFn };
    t.join();

    LogWithThread("Main thread: EXIT");
}

void ThreadFn()
{
    LogWithThread("Worker thread: ENTER");

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));

    LogWithThread("Worker thread: EXIT");
}

void LogWithThread(const std::string_view msg)
{
    std::cout << "[" << std::this_thread::get_id() << "] ";
    std::cout << msg << std::endl;
}