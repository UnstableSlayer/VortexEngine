//#pragma once
//#include <coroutine>
//#include <SDL2/SDL.h>
//
//namespace Vortex
//{		
//	enum class JobPriority
//	{
//		Low, Normal, High, Critical
//	};
//
//	template<typename T>
//	class JobReturnData
//	{
//	private:
//		struct promise_type;
//		using coHandle = std::coroutine_handle<promise_type>;
//
//		struct promise_type
//		{
//			T value_;
//			std::exception_ptr exception_;
//
//			JobReturnData get_return_object()
//			{
//				return { handle = coHandle::from_promise(*this) };
//			}
//
//			std::suspend_never initial_suspend() { return {}; }
//			std::suspend_always final_suspend() noexcept { return {}; }
//
//			void unhandled_exception()
//			{
//				exception_ = std::current_exception();
//			}
//
//			template<std::convertible_to<T> From>
//			std::suspend_always yield_value(From&& from)
//			{
//				value_ = std::forward<From>(from);
//				return {};
//			}
//			void return_void() {}
//		};
//
//	public:
//		JobReturnData(coHandle Handle) : handle(Handle) {}
//		~JobReturnData() { handle.destroy(); }
//
//		const bool Done() 
//		{
//			fill();
//			return handle.done();
//		}
//
//		T GetValue()
//		{
//			fill();
//			full = false;
//			return std::move(handle.promise().value_);
//		}
//
//	public:
//
//	public:
//		coHandle handle;
//		JobPriority priority;
//
//	private:
//		bool full = false;
//
//		void fill()
//		{
//			if (!full)
//			{
//				handle();
//				if (handle.promise().exception_)
//					std::rethrow_exception(handle.promise().exception_);
//				full = true;
//			}
//		}
//	};
//}