// thread_pool.hpp
// 
// Minimal thread pool implementation;
// does not support waitable tasks, thread-local work queues,
// or work stealing among worker threads.

#ifndef THREAD_POOL_BASIC_HPP
#define THREAD_POOL_BASIC_HPP

#include <atomic>
#include <thread>
#include <vector>
#include <exception>
#include <functional>
#include <condition_variable>

#include <cdl/concurrent/queue.hpp>
#include <cdl/thread/thread_joiner.hpp>

class thread_pool
{
private:
	cdl::concurrent::queue<std::function<void()>> work_queue;

	std::size_t const n_threads;

	std::atomic_bool         exit_flag;
	std::atomic_bool         accepting_flag;
	std::vector<std::thread> threads;

	cdl::thread::thread_joiner joiner;
	
	mutable std::mutex      empty_mutex;
	std::condition_variable empty_cv;

public:
	explicit thread_pool(
		std::size_t const n_threads_ = std::thread::hardware_concurrency())
		: n_threads{n_threads_} 
		, exit_flag{ false }
		, accepting_flag{ true }
		, threads{}
		, joiner{threads}
		, empty_mutex{}
		, empty_cv{}
	{
		try
		{
			for (auto i = 0ul; i < n_threads; ++i)
			{
				threads.emplace_back(&thread_pool::worker_loop, this);
			}
		}
		catch (...)
		{
			exit_flag = true;
			throw;
		}
	}

	~thread_pool()
	{
		exit_flag = true;
		
		// thread_joiner instance ensures that all 
		// threads are joined on destruction of the pool
	}

	void shutdown()
	{
		std::unique_lock<std::mutex> lock{empty_mutex};

		accepting_flag = false;
		empty_cv.wait(lock, 
			[this] { return work_queue.is_empty_unsafe(); });
	}

	template <typename Function>
	void submit(Function work)
	{
		if (!accepting_flag)
		{
			throw std::runtime_error{"Attempting Submit to Closed Thread Pool"};
		}

		work_queue.push(std::function<void()>{work});
	}

private:
	void worker_loop()
	{
		while (!exit_flag)
		{
			std::function<void()> task;
			if (work_queue.try_pop(task))
			{
				task();
			}
			else
			{
				empty_cv.notify_one();
				std::this_thread::yield();
			}
		}
	}
};

#endif // THREAD_POOL_BASIC_HPP