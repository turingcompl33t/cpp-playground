// tatas_ex.hpp
//
// An extended variant of the "test-and-test-and-set" lock
// that utilizes a bitset in place of the usual boolean flag
// in order to implement a naive multi-resource lock.
//
// Adapted from the pseudocode in the thesis work:
// "High-Performance Composable Transactional Data Structures"
// by Deli Zhang

#ifndef TATAS_EX_HPP
#define TATAS_EX_HPP

#include <atomic>
#include <cstdint>

using bitset_t = uint64_t;

class tatas_ex_lock
{
    std::atomic<bitset_t> bitset;

public:
    tatas_ex_lock()
        : bitset{0} {}

    ~tatas_ex_lock() = default;

    // non-copyable
    tatas_ex_lock(tatas_ex_lock const&) = delete;
    tatas_ex_lock& operator=(tatas_ex_lock const&) = delete;

    // non-movable
    tatas_ex_lock(tatas_ex_lock&&)            = delete;
    tatas_ex_lock& operator=(tatas_ex_lock&&) = delete; 

    void lock(bitset_t request)
    {
        auto current = bitset.load(std::memory_order_relaxed);
        do
        {
            if (current & request)
            {
                // spin on conflict; avoids unnecessary atomic operation
                continue;
            }
        } while (!bitset.compare_exchange_weak(
            current, 
            current | request, 
            std::memory_order_relaxed));
    }

    void unlock(bitset_t request)
    {
        auto current = bitset.load(std::memory_order_relaxed);
        while (!bitset.compare_exchange_weak(
            current, 
            current & ~request, 
            std::memory_order_relaxed));
    }
};

#endif // TATAS_EX_HPP