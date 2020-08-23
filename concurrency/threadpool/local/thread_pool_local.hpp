// thread_pool_local.hpp
//
// An extension of the simple thread pool implementation
// (simple_thread_pool) that adds thread-local work queues
// but does not introduce a work-stealing algorithm.

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

#include <cdl/concurrent/queue.hpp>

#include "function_wrapper.hpp"

class thread_pool_local
{
	cdl::concurrent::queue<
		function_wrapper> pool_work_queue;

	// thread-local work queues need not be synchronized
	using local_queue_type = std::queue<function_wrapper>;
	static thread_local std::unique_ptr<local_queue_type> local_work_queue;

	std::size_t const n_threads;

	std::atomic_bool         exit_flag;
	std::atomic_bool         accepting_flag;
	std::vector<std::thread> threads;

	mutable std::mutex      empty_mutex;
	std::condition_variable empty_cv;

public:
	explicit thread_pool_local(
		std::size_t const n_threads_ = std::thread::hardware_concurrency())
		: n_threads{n_threads_}
		, exit_flag{false}
		, accepting_flag{true}	
		, threads{}
		, empty_mutex{}
		, empty_cv{}
	{
		try
		{
			for (auto i = 0ul; i < n_threads; ++i)
			{
				threads.emplace_back(
					&thread_pool_local::worker_loop, 
					this);
			}
		}
		catch (...)
		{
			exit_flag = true;
			throw;
		}
	}

	~thread_pool_local()
	{
		exit_flag = true;
	}

	void shutdown()
	{
		std::unique_lock<std::mutex> lock{empty_mutex};

		accepting_flag = false;
		empty_cv.wait(lock, 
			[this] { return pool_work_queue.is_empty_unsafe(); });
	}

	// TODO: replace std::result_of_t with std::invoke_result_t
	// currently, this fails to link with a disgusting linker error

	template <typename FunctionType>
	std::future<typename std::result_of_t<FunctionType()>>
	submit(FunctionType fn)
	{
		using result_type = typename std::result_of_t<FunctionType()>;

		std::packaged_task<result_type()> task(fn);
		auto fut = task.get_future();

		if (local_work_queue)
		{
			local_work_queue->push(std::move(task));
		}
		else
		{
			pool_work_queue.push(std::move(task));
		}

		return fut;
	}



private:
	void worker_loop()
	{
		local_work_queue.reset(new local_queue_type);

		while (!exit_flag)
		{
			run_pending_task();
		}
	}

	void run_pending_task()
	{
		function_wrapper task{};
		if (local_work_queue && !local_work_queue->empty())
		{
			// execute work from local work queue 
			task = std::move(local_work_queue->front());
			local_work_queue->pop();
			task();
		}
		else if (pool_work_queue.try_pop(task))
		{
			// execute work from central pool queue
			task();
		}
		else
		{
			empty_cv.notify_one();
			std::this_thread::yield();
		}
	}
};

#endif // THREAD_POOL_LOCAL_HPP