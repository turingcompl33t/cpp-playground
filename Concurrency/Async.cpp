// Async.cpp
// Demo of the C++11 async API.

#include <chrono>
#include <thread>
#include <future>
#include <iostream>
#include <string_view>

// milliseconds
constexpr auto SLEEP_TIME = 5000;

void ThreadFn();

void LogWithThread(const std::string_view msg);

int main()
{
    LogWithThread("Main thread: ENTER");

    auto future = std::async(std::launch::deferred, ThreadFn);
    future.get();

    LogWithThread("Main thread: EXIT");

    return 0;
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