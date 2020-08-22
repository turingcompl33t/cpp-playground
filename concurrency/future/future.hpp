// future.hpp
//
// An inefficient, hand-rolled implementation of some of the
// facilities provided by the standard library <future> header.

#include <mutex>
#include <memory>
#include <utility>
#include <exception>
#include <condition_variable>

namespace detail
{

    // The dynamically allocated shared state used to 
    // communicate between future and promise instances.
    template <typename R>
    struct shared_state
    {
        R value_;
        std::exception_ptr exception_;
        bool ready_ = false;
        std::mutex mutex_;
        std::condition_variable cv_;
    };
}


// Error codes carried by future_error instances.
enum class future_errc
{
    no_state,
    future_already_retrieved,
    promise_already_satisifed,
    broken_promise
};


// Custom exception class for future API.
struct future_error
{
    explicit future_error(future_errc errc)
    : errc_{errc}
    {}

    future_errc type() const noexcept
    {
        return errc_;
    }

private:
    future_errc errc_;
};


// Future primitive implementation.
template <typename R> 
struct future
{
    std::shared_ptr<detail::shared_state<R>> state_;

    void wait() const
    {
        if (!state_) throw future_error{future_errc::no_state};
        std::unique_lock<std::mutex> lock{state_->mutex_};
        while (!state_->ready_) state_->cv_.wait(lock);
    }

    R get()
    {
        wait();

        // invalidate this future after this line
        auto sp = std::move(state_);
        if (sp->exception_)
        {
            std::rethrow_exception(sp->exception_);
        }
        return std::move(sp->value_);        
    }

    bool valid() const
    {
        return (state_ != nullptr);
    }

    bool ready() const
    {
        if (!state_) return false;
        std::lock_guard<std::mutex> guard{state_->mutex_};
        return state_->ready_;
    }
};


// Promise primitive implementation.
template <typename R> 
struct promise
{
private:
    std::shared_ptr<detail::shared_state<R>> state_;
    bool future_already_retrieved_ = false;

public:
    promise()
        : state_{ std::make_shared<detail::shared_state<R>>() }
    {}

    ~promise()
    {
        abandon_state();
    }

    future<R> get_future()
    {
        if (!state_) throw future_error{future_errc::no_state};
        if (future_already_retrieved_) throw future_error{future_errc::future_already_retrieved};
        future_already_retrieved_ = true;
        return future<R>{state_};
    }

    void set_value(R value)
    {
        if (!state_) throw future_error{future_errc::no_state};
        if (state_->ready_) throw future_error{future_errc::promise_already_satisifed};
        state_->value_ = std::move(value);
        set_ready();
    }

    void set_exception(std::exception_ptr p)
    {
        if (!state_) throw future_error{future_errc::no_state};
        if (state_->ready_) throw future_error{future_errc::promise_already_satisifed};
        state_->exception_ = std::move(p);
        set_ready();
    }

    void set_ready()
    {
        std::lock_guard<std::mutex> guard{state_->mutex_};
        state_->ready_ = true;
        state_->cv_.notify_one();        
    
    }

private:
    void abandon_state()
    {
        if (!state_ || !future_already_retrieved_) return;
        std::lock_guard<std::mutex> guard{state_->mutex_};
        if (state_->ready_) return;
        state_->exception_ = std::make_exception_ptr(future_error{future_errc::broken_promise});
        state_->ready_ = true;
        state_->cv_.notify_one();
    }
};