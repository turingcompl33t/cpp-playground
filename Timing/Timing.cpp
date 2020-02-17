// Timing.cpp
// Demo of basic C++ timing facilities.
//
// Compile:
//  cl /EHsc /nologo /std:c++17 Timing.cpp

#include <thread>
#include <chrono>
#include <iostream>

// required for use of chrono literals
// e.g. in the call to sleep_for()
using namespace std::literals::chrono_literals;

void spin();

struct timer
{
    timer()
    {
        start = std::chrono::high_resolution_clock::now();
    }

    ~timer()
    {
        end = std::chrono::high_resolution_clock::now();

        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Timer: " << ms.count() << "ms " << std::endl;
    }

private:
    std::chrono::time_point<std::chrono::steady_clock> start;
    std::chrono::time_point<std::chrono::steady_clock> end;
};

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    std::this_thread::sleep_for(1s);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> duration{end - start};
    std::cout << duration.count() << "s " << std::endl;

    spin();

    return 0;
}

void spin()
{
    timer t{};

    std::this_thread::sleep_for(3s);
}