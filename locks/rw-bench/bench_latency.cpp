// bench_latency.cpp
// Benchmarking the average latency for reader-writer lock acquire operations.

#include <array>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <future>
#include <numeric>
#include <thread>
#include <tuple>
#include <vector>

// the contenders
#include "lock_helpers.hpp"

constexpr static auto const MIN_WORKERS = 2UL;
constexpr static auto const MAX_WORKERS = 64UL;

// the number of lock acquire operations performed by each worker
constexpr static auto const REPS_PER_WORKER = 1000UL;

// the number of iterations performed for each configuration
constexpr static auto const ITERS_PER_CONFIG = 100UL;

// proportion of writer workers
constexpr static std::array PROPS{0.1, 0.5};

using duration_t = std::chrono::microseconds;

using result_t =
    std::tuple<std::size_t, double, duration_t::rep, duration_t::rep>;

auto report_progress(std::size_t const count, std::size_t const total) -> void {
  fprintf(stderr, "Completed %zu/%zu\n", count, total);
}

template <typename LockType>
auto reader(LockType& lock, Latch& latch) -> duration_t::rep {
  using clock = std::chrono::high_resolution_clock;
  std::vector<duration_t::rep> durations{};
  durations.reserve(REPS_PER_WORKER);

  latch.arrive_and_wait();

  for (auto _ = 0UL; _ < REPS_PER_WORKER; ++_) {
    auto const start = clock::now();
    acquire_read(lock);
    auto const stop = clock::now();
    release_read(lock);
    auto const time = std::chrono::duration_cast<duration_t>(stop - start);
    durations.push_back(time.count());
  }
  auto const avg =
      std::accumulate(durations.cbegin(), durations.cend(), duration_t::rep{}) /
      static_cast<duration_t::rep>(REPS_PER_WORKER);
  return avg;
}

template <typename LockType>
auto writer(LockType& lock, Latch& latch) -> duration_t::rep {
  using clock = std::chrono::high_resolution_clock;
  std::vector<duration_t::rep> durations{};
  durations.reserve(REPS_PER_WORKER);

  latch.arrive_and_wait();

  for (auto _ = 0UL; _ < REPS_PER_WORKER; ++_) {
    auto const start = clock::now();
    acquire_write(lock);
    auto const stop = clock::now();
    release_write(lock);
    auto const time = std::chrono::duration_cast<duration_t>(stop - start);
    durations.push_back(time.count());
  }
  auto const avg =
      std::accumulate(durations.cbegin(), durations.cend(), duration_t::rep{}) /
      static_cast<duration_t::rep>(REPS_PER_WORKER);
  return avg;
}

template <typename LockType>
auto run_one_iteration(std::size_t const n_writers, std::size_t const n_readers)
    -> std::pair<duration_t::rep, duration_t::rep> {
  auto const total_workers = n_writers + n_readers;

  Latch latch{total_workers};
  LockType lock{};

  std::vector<std::future<duration_t::rep>> w_futs{};
  std::vector<std::future<duration_t::rep>> r_futs{};
  for (auto _ = 0UL; _ < n_writers; ++_) {
    w_futs.emplace_back(std::async(std::launch::async, writer<LockType>,
                                   std::ref(lock), std::ref(latch)));
  }
  for (auto _ = 0UL; _ < n_readers; ++_) {
    r_futs.emplace_back(std::async(std::launch::async, reader<LockType>,
                                   std::ref(lock), std::ref(latch)));
  }

  // bench begins once the final task is launched

  std::vector<duration_t::rep> w_avgs{};
  std::vector<duration_t::rep> r_avgs{};

  std::transform(w_futs.begin(), w_futs.end(), std::back_inserter(w_avgs),
                 [](auto& fut) { return fut.get(); });
  std::transform(r_futs.begin(), r_futs.end(), std::back_inserter(r_avgs),
                 [](auto& fut) { return fut.get(); });

  auto const w_avg =
      std::accumulate(w_avgs.cbegin(), w_avgs.cend(), duration_t::rep{}) /
      static_cast<duration_t::rep>(n_writers);
  auto const r_avg =
      std::accumulate(r_avgs.cbegin(), r_avgs.cend(), duration_t::rep{}) /
      static_cast<duration_t::rep>(n_readers);
  return std::make_pair(w_avg, r_avg);
}

template <typename LockType, typename Callback>
auto bench_latency(Callback&& with_results) -> void {
  std::vector<result_t> results{};
  results.reserve((MAX_WORKERS - MIN_WORKERS + 1) * PROPS.size());

  auto count = 0UL;
  auto const total = (MAX_WORKERS - MIN_WORKERS + 1) * PROPS.size();

  for (auto n_workers = MIN_WORKERS; n_workers <= MAX_WORKERS; n_workers += 1) {
    for (auto const prop : PROPS) {
      auto const n_writers = std::max(
          static_cast<std::size_t>(static_cast<double>(n_workers) * prop), 1UL);
      auto const n_readers =
          std::max(static_cast<std::size_t>(static_cast<double>(n_workers) *
                                            (1.0 - prop)),
                   1UL);

      std::vector<duration_t::rep> writer_res{};
      std::vector<duration_t::rep> reader_res{};
      writer_res.reserve(ITERS_PER_CONFIG);
      reader_res.reserve(ITERS_PER_CONFIG);
      for (auto _ = 0UL; _ < ITERS_PER_CONFIG; ++_) {
        auto const [w, r] = run_one_iteration<LockType>(n_writers, n_readers);
        writer_res.push_back(w);
        reader_res.push_back(r);
      }

      auto const avg_w = std::accumulate(writer_res.cbegin(), writer_res.cend(),
                                         duration_t::rep{}) /
                         static_cast<duration_t::rep>(ITERS_PER_CONFIG);
      auto const avg_r = std::accumulate(reader_res.cbegin(), reader_res.cend(),
                                         duration_t::rep{}) /
                         static_cast<duration_t::rep>(ITERS_PER_CONFIG);

      results.emplace_back(n_workers, prop, avg_w, avg_r);
      report_progress(++count, total);
    }
  }

  std::forward<Callback>(with_results)(results);
}

auto dump_results(std::vector<result_t> const& results) -> void {
  for (const auto& [n, prop, w_avg, r_avg] : results) {
    printf("%zu,%f,%ld,%ld\n", n, prop, w_avg, r_avg);
  }
}

auto main() -> int {
  bench_latency<std::shared_mutex>(dump_results);
  bench_latency<tbb::reader_writer_lock>(dump_results);
  return EXIT_SUCCESS;
}