// thread_pool_local.hpp
//
// An extension of the simple thread pool implementation
// (simple_thread_pool) that adds thread-local work queues to reduce contention.

#ifndef THREAD_POOL_LOCAL_HPP
#define THREAD_POOL_LOCAL_HPP

#include <queue>
#include <mutex>
#include <future>
#include <thread>
#include <atomic>
#include <vector>
#include <exception>
#include <condition_variable>

#include "function_wrapper.hpp"

class thread_pool_local
{
	queue<function_wrapper> pool_work_queue_;

	using local_queue_type = std::queue<function_wrapper>;
	static thread_local std::unique_ptr<local_queue_type> local_work_queue_;

	std::atomic_bool         exit_;
	std::atomic_bool         accepting_;
	std::vector<std::thread> threads_;

	mutable std::mutex      empty_mutex_;
	std::condition_variable empty_cv_;

public:
	thread_pool_local()
		: accepting_{ true }
		, exit_{ false }	
	{
		unsigned const thread_count = std::thread::hardware_concurrency();

		try
		{
			for (unsigned i = 0; i < thread_count; ++i)
			{
				threads_.push_back(
					std::thread{ &thread_pool_local::worker_thread, this }
				);
			}
		}
		catch (...)
		{
			exit_ = true;
			throw;
		}
	}

	~thread_pool_local()
	{
		exit_ = true;
	}

	void shutdown()
	{
		std::unique_lock<std::mutex> lock{ empty_mutex_ };

		accepting_ = false;
		empty_cv_.wait(lock, [this] { return pool_work_queue_.empty(); });
	}

	template <typename FunctionType>
	std::future<typename std::result_of_t<FunctionType()>>
	submit(FunctionType fn)
	{
		using result_type = typename std::result_of_t<FunctionType()>;

		std::packaged_task<result_type()> task(fn);
		auto fut = task.get_future();

		if (local_work_queue_)
		{
			local_work_queue_->push(std::move(task));
		}
		else
		{
			pool_work_queue_.push(std::move(task));
		}

		return fut;
	}

	void run_pending_task()
	{
		function_wrapper task;
		if (local_work_queue_ && !local_work_queue_->empty())
		{
			// execute work from local work queue 
			task = std::move(local_work_queue_->front());
			local_work_queue_->pop();
			task();
		}
		else if (pool_work_queue_.try_pop(task))
		{
			// execute work from central pool queue
			task();
		}
		else
		{
			empty_cv_.notify_one();
			std::this_thread::yield();
		}
	}

private:
	void worker_thread()
	{
		local_work_queue_.reset(new local_queue_type);

		while (!exit_)
		{
			run_pending_task();
		}
	}
};

#endif // THREAD_POOL_LOCAL_HPP