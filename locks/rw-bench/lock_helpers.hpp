// lock_helpers.hpp

#ifndef LOCK_HELPERS_HPP
#define LOCK_HELPERS_HPP

#include <shared_mutex>
#include <tbb/reader_writer_lock.h>

#include <xmmintrin.h>

template <typename LockType> class ReadGuard {
  static_assert("Don't instantiate this primary template!");
};

template <> class ReadGuard<std::shared_mutex> {
  std::shared_mutex& lock_;

public:
  explicit ReadGuard(std::shared_mutex& lock)
      : lock_{lock} {
    lock_.lock_shared();
  }
  ~ReadGuard() { lock_.unlock_shared(); }
};

template <> class ReadGuard<tbb::reader_writer_lock> {
  tbb::reader_writer_lock& lock_;

public:
  explicit ReadGuard(tbb::reader_writer_lock& lock)
      : lock_{lock} {
    lock_.lock_read();
  }
  ~ReadGuard() { lock_.unlock(); }
};

template <typename LockType> class WriteGuard {
  static_assert("Don't instantiate this primary template!");
};

template <> class WriteGuard<std::shared_mutex> {
  std::shared_mutex& lock_;

public:
  explicit WriteGuard(std::shared_mutex& lock)
      : lock_{lock} {
    lock_.lock();
  }
  ~WriteGuard() { lock_.unlock(); }
};

template <> class WriteGuard<tbb::reader_writer_lock> {
  tbb::reader_writer_lock& lock_;

public:
  explicit WriteGuard(tbb::reader_writer_lock& lock)
      : lock_{lock} {
    lock_.lock();
  }
  ~WriteGuard() { lock_.unlock(); }
};

// dead-simple synchronization latch with busy-waiting
class Latch {
  std::size_t const count_;
  std::atomic<std::size_t> arrived_{0};

public:
  explicit Latch(std::size_t const count)
      : count_{count} {}
  auto arrive_and_wait() noexcept -> void {
    arrived_.fetch_add(1);
    while (arrived_.load() != count_) {
      _mm_pause();
    }
  }
};

auto acquire_read(std::shared_mutex& lock) -> void { lock.lock_shared(); }

auto release_read(std::shared_mutex& lock) -> void { lock.unlock_shared(); }

auto acquire_read(tbb::reader_writer_lock& lock) -> void { lock.lock_read(); }

auto release_read(tbb::reader_writer_lock& lock) -> void { lock.unlock(); }

auto acquire_write(std::shared_mutex& lock) -> void { lock.lock(); }

auto release_write(std::shared_mutex& lock) -> void { lock.unlock(); }

auto acquire_write(tbb::reader_writer_lock& lock) -> void { lock.lock(); }

auto release_write(tbb::reader_writer_lock& lock) -> void { lock.unlock(); }

#endif  // LOCK_HELPERS_HPP
