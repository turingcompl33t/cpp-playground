// monotonic_buffer.cpp
// Little exploration of std::pmr::monotonic_buffer_allocator.

#include <vector>
#include <iostream>
#include <memory_resource>

constexpr static auto const POOL_SIZE = 128;

int main()
{
    char buffer[POOL_SIZE] = {};
    std::fill_n(std::begin(buffer), std::size(buffer)-1, '-');
    std::cout << buffer << '\n';

    auto pool = std::pmr::monotonic_buffer_resource{std::data(buffer), std::size(buffer)};

    auto v = std::pmr::vector<char>{&pool};
    for (auto c = 'a'; c <= 'z'; ++c)
    {
        v.push_back(c);
    }
    std::cout << buffer << '\n';
}