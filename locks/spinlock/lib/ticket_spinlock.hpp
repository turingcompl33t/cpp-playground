// ticket_spinlock.hpp
// A ticket-granting spinlock that ensures first-in first-out behavior.
//
// Without C++20 atomics, this implementation is basically just a
// slight modification to a naive spinlock...

#ifndef TICKET_SPINLOCK_HPP
#define TICKET_SPINLOCK_HPP

#include <atomic>

// NOTE: why is this not a member of std on my system??
constexpr static auto const HARDWARE_DESTRUCTIVE_INTERFERENCE_SIZE{64};

class ticket_spinlock {
  alignas(HARDWARE_DESTRUCTIVE_INTERFERENCE_SIZE)
      std::atomic<std::size_t> in_count{0};
  alignas(HARDWARE_DESTRUCTIVE_INTERFERENCE_SIZE)
      std::atomic<std::size_t> out_count{0};

public:
  ticket_spinlock() = default;
  ~ticket_spinlock() = default;

  ticket_spinlock(ticket_spinlock const&) = delete;
  ticket_spinlock& operator=(ticket_spinlock const&) = delete;

  ticket_spinlock(ticket_spinlock&&) = delete;
  ticket_spinlock& operator=(ticket_spinlock&&) = delete;

  auto acquire() -> void {
    auto const my_ticket = in_count.fetch_add(1, std::memory_order_acquire);
    for (;;) {
      auto const now = out_count.load(std::memory_order_acquire);
      if (now == my_ticket) {
        return;
      }

      // C++20
      // out.wait(now, std::memory_order_relaxed);
    }
  }

  auto release() -> void {
    out_count.fetch_add(1, std::memory_order_release);

    // c++20
    // out_count.notify_all();
  }
};

#endif  // TICKET_SPINLOCK_HPP
