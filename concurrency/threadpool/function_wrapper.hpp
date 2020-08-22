// function_wrapper.hpp
//
// Custom function wrapper implementation for use in thread pools.

#ifndef FUNCTION_WRAPPER_HPP
#define FUNCTION_WRAPPER_HPP

#include <memory>
#include <utility>

// A custom callable wrapper that handles move-only types.
//
// thread pools accept work in the form of a std::function<> 
// instance; however, this is no longer possible in the event 
// that std::packaged_task is used to represent units of work 
// because std::function requires that stored function objects 
// are copy-constructible

class function_wrapper
{
	struct impl_base
	{
		virtual void call() = 0;
		virtual ~impl_base() {}
	};

	std::unique_ptr<impl_base> impl_;

	template <typename FunctionType>
	struct impl_type : impl_base
	{
		FunctionType fn_;
		impl_type(FunctionType&& fn) : fn_{ std::move(fn) } {}
		void call() { fn_(); }
	};

public:

	function_wrapper() = default;

	template <typename FunctionType>
	function_wrapper(FunctionType&& fn)
		: impl_{ std::make_unique<impl_type<FunctionType>>(std::move(fn)) }
	{}

	function_wrapper(function_wrapper&& other)
		: impl_{ std::move(other.impl_) }
	{}

	function_wrapper& operator=(function_wrapper&& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		impl_ = std::move(rhs.impl_);
		return *this;
	}

	function_wrapper(function_wrapper&)            = delete;
	function_wrapper(function_wrapper const&)      = delete;
	function_wrapper& operator=(function_wrapper&) = delete;

	void operator()()
	{
		impl_->call();
	}
};

#endif // FUNCTION_WRAPPER_HPP