// HardwareConcurrency.cpp
// Demo of C++11 implementation concurrency detection support.

#include <thread>
#include <iostream>

int main()
{
    auto n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads supported by implementation" << std::endl;
}