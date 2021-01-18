// naive_spinlock.hpp
// Dead-simple spinlock using std::atomic_flag.

#ifndef NAIVE_SPINLOCK_HPP
#define NAIVE_SPINLOCK_HPP

#include <atomic>

class naive_spinlock {
  std::atomic_flag locked{};

public:
  constexpr naive_spinlock()
      : locked{} {}

  ~naive_spinlock() = default;

  naive_spinlock(naive_spinlock const&) = delete;
  naive_spinlock& operator=(naive_spinlock const&) = delete;

  naive_spinlock(naive_spinlock&&) = delete;
  naive_spinlock& operator=(naive_spinlock&&) = delete;

  auto acquire() -> void {
    while (locked.test_and_set(std::memory_order_acquire)) {
      ;
    }
  }

  auto release() -> void { locked.clear(std::memory_order_release); }
};

#endif  // NAIVE_SPINLOCK_HPP