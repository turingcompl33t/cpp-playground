// mrlock.hpp

#ifndef MRLOCK_HPP
#define MRLOCK_HPP

#include <atomic>
#include <cstdint>
#include <cstdlib>
#include <stdexcept>

// limits us to a maximum of 64 resources protected by a single mrlock instance
using bitset_t = std::uint64_t;

// sequence number
using seq_t = std::uint32_t;

// TODO: move this inside mrlock
// only makes sense in context of higher level class
struct cell
{
    std::atomic<seq_t> seq;
    bitset_t           bits;
};

// TODO: move this inside mrlock
// only makes sense in context of higher level class
class request_handle
{
    std::uint32_t position;

public:
    constexpr request_handle() 
        : position{0} {}

    constexpr explicit request_handle(std::uint32_t const position_)
        : position{position_} {}

    friend class mrlock;
};

class mrlock
{
    // The buffer of cells that compose the request queue.
    cell* buffer;

    // Integral mask for fast conversion from head / tail -> index.
    std::uint32_t mask;

    // Head and tail indices;
    // these indices increase monotonically throughout mrlock lifetime.
    std::atomic<std::uint32_t> head;
    std::atomic<std::uint32_t> tail;

public:
    mrlock(std::size_t const capacity)
        : buffer{new cell[capacity]}
        , mask{capacity - 1}
        , head{0}
        , tail{0}
    {
        // TODO: capacity must be power of 2

        for (auto i = 0u; i < capacity; ++i)
        {
            buffer[i].bits = 0;
            buffer[i].seq  = i;
        }
    }

    ~mrlock()
    {
        delete[] buffer;
    }

    // non-copyable
    mrlock(mrlock const&)            = delete;
    mrlock& operator=(mrlock const&) = delete;

    // non-movable
    mrlock(mrlock&&)            = delete;
    mrlock& operator=(mrlock&&) = delete;

    [[nodiscard]]
    request_handle lock(bitset_t const request)
    {
        cell*         c{};
        std::uint32_t pos{};
        for (;;)
        {
            pos = tail.load(std::memory_order_relaxed);
            c   = &buffer[pos & mask];

            auto const seq = c->seq.load(std::memory_order_acquire);
            
            auto const diff = static_cast<std::int32_t>(seq) 
                - static_cast<std::int32_t>(pos);
            if (0 == diff)
            {   
                if (tail.compare_exchange_weak(pos, pos + 1, std::memory_order_relaxed))
                {
                    // successfully incremented the tail; we have our cell
                    break;
                }
            }
        }

        // update the contents of our cell
        c->bits = request;
        c->seq.store(pos + 1, std::memory_order_release);

        // spin until all of our requested resources are available
        auto spin = head.load(std::memory_order_relaxed);
        while (spin != pos)
        {
            if (pos - buffer[spin & mask].seq > mask 
            || !(buffer[spin & mask].bits & request))
            {
                ++spin;
            }
        }

        return request_handle{pos};
    }

    void unlock(request_handle const& handle)
    {
        buffer[handle.position & mask].bits = 0;

        auto pos = head.load(std::memory_order_relaxed);
        while (0 == buffer[pos & mask].bits)
        {
            cell* c = &buffer[pos & mask];
            auto const seq = c->seq.load(std::memory_order_acquire);

            auto const diff = static_cast<std::int32_t>(seq) 
                - static_cast<std::int32_t>(pos + 1);
            if (0 == diff)
            {
                if (head.compare_exchange_weak(pos, pos + 1, std::memory_order_relaxed))
                {
                    c->bits = ~0;
                    c->seq.store(pos + mask + 1, std::memory_order_release);
                }
            }

            pos = head.load(std::memory_order_relaxed);
        }
    }
};

// helper class to avoid manual management of 
// lock() / unlock() and maintaining the request handle
class scoped_mrlock
{
    mrlock&        lock;
    request_handle handle;

public:
    scoped_mrlock(mrlock& lock_, bitset_t const request)
        : lock{lock_}
        , handle{}
    {
        handle = lock.lock(request);
    }

    ~scoped_mrlock()
    {
        lock.unlock(handle);
    }

    scoped_mrlock(scoped_mrlock const&)            = delete;
    scoped_mrlock& operator=(scoped_mrlock const&) = delete;

    scoped_mrlock(scoped_mrlock&&)            = delete;
    scoped_mrlock& operator=(scoped_mrlock&&) = delete;
};

#endif // MRLOCK_HPP