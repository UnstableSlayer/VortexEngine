#pragma once
#include <coroutine>

namespace Vortex
{	
	typedef void* JobAddress;
	struct JobEntry
	{
		JobAddress addr;
		uintptr_t ptr;
		uint32_t* refCount;
	};

	template<typename T>
	class JobData
	{
	public:
		struct promise_type;
		using JobHandle = std::coroutine_handle<promise_type>;

		struct promise_type
		{
			Ref<T> value_;
			std::exception_ptr exception_;

			JobData get_return_object()
			{
				return JobData(JobHandle::from_promise(*this));
			}

			std::suspend_always initial_suspend() { return {}; }
			std::suspend_always final_suspend() noexcept { return {}; }

			void unhandled_exception()
			{
				exception_ = std::current_exception();
			}

			template<std::convertible_to<T> From>
			std::suspend_always yield_value(From&& from)
			{
				if (!value_.Get()) value_ = Ref<T>(new T());
				*value_ = std::forward<From>(from);
				return {};
			}

			template<std::convertible_to<T> From>
			void return_value(From&& from)
			{
				if (!value_.Get()) value_ = Ref<T>(new T());
				*value_ = std::forward<From>(from);
			}

			void SetReturnPtr(const uintptr_t addr, uint32_t* refCounter = nullptr)
			{
				value_ = Ref<T>(reinterpret_cast<T*>(addr), refCounter);
			}
			JobEntry GetReturnPtr()
			{
				return { nullptr, reinterpret_cast<uintptr_t>(value_.Get()), value_.GetRefCount() };
			}

		};

	public:
		JobData() : handle(nullptr) {}
		JobData(JobHandle Handle) : handle(Handle) {}
		~JobData() {}

		void SetJobEntry(JobEntry entry)
		{
			handle = handle.from_address(entry.addr);
			handle.promise().SetReturnPtr(entry.ptr, entry.refCount);
		}
		const JobEntry GetJobEntry() const
		{
			JobEntry promiseEntry = handle.promise().GetReturnPtr();
			return { handle.address(), promiseEntry.ptr, promiseEntry.refCount };
		}

		constexpr bool await_ready() noexcept { return isDone(); }

		template<typename F>
		void await_suspend(std::coroutine_handle<F> h) const
		{
			handle.resume();
			h.resume();
		}

		Ref<T> await_resume() 
		{
			yield();
			yielded = false;
			return handle.promise().value_;
		}

		void Destroy()
		{
			if(handle) handle.destroy();
		}

		bool isDone()
		{
			if (!handle)
				return true;

			yield();
			return handle.done();
		}

		explicit operator bool()
		{
			return !isDone();
		}

		Ref<T> operator()()
		{
			yield();
			yielded = false;
			return handle.promise().value_;
		}

	public:
		JobHandle handle;

	private:
		bool yielded = false;

		void yield()
		{
			if (!yielded && !handle.done())
			{
				handle();
				if (handle.promise().exception_)
					std::rethrow_exception(handle.promise().exception_);
				yielded = true;
			}
		}
	};
}