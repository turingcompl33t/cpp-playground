// Timer.cpp
// Timer class implementation.

#include <chrono>
#include <string>
#include <thread>
#include <iostream>

struct timer
{
    timer(const std::string& label = "")
        : label{label}
    {
        start_timepoint = std::chrono::high_resolution_clock::now();
    }

    ~timer()
    {
        stop();
    }

    void stop()
    {
        auto end_timepoint = std::chrono::high_resolution_clock::now();

        auto start = 
            std::chrono::time_point_cast<std::chrono::microseconds>(start_timepoint)
            .time_since_epoch()
            .count();
        
        auto end = 
            std::chrono::time_point_cast<std::chrono::microseconds>(end_timepoint)
            .time_since_epoch()
            .count();

        auto duration = end - start;
        double ms = duration * 0.001;
        
        // output result to console
        std::cout << "[WDL] (" << label << ") " << ms << "ms\n";
    }

private:
    std::string label;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_timepoint;
};

void spin()
{
    using namespace std::chrono_literals;

    timer t{"spin()"};

    std::this_thread::sleep_for(2s);
}

int main()
{
    std::cout << "main() - start\n";

    spin();

    std::cout << "main() - end\n";
}