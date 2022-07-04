#pragma once
#include "Assert.h"
#include "Logger.h"

//#define REF_COUNTER_DEBUG;

namespace Vortex
{
	template<typename T>
	class VORTEX_API Unique
	{
	public:
	    Unique()
		{
		    m_Ptr = nullptr;
	    }
	    Unique(T* ptr)
		{
            m_Ptr = ptr;
        }
		Unique(Unique<T>&& uptr)
		{
            m_Ptr = std::move(uptr.m_Ptr);
            uptr.m_Ptr = nullptr;
        }

		~Unique()
		{
            delete m_Ptr;
        }

        inline explicit operator bool() const { return m_Ptr; }

		Unique<T>& operator=(Unique<T>&& uptr)
		{
            if (this == uptr) return *this;
            m_Ptr = std::move(uptr.m_Ptr);
            uptr.m_Ptr = nullptr;
            return *this;
        }

    public:
		inline T* Get() const { return m_Ptr; }
		inline T* operator ->() const { return m_Ptr; }
		inline T& operator *() const { return *m_Ptr; }

        Unique(const Unique<T>& uptr) = delete;
        Unique<T>& operator=(const Unique<T>& uptr) = delete;

	private:
	    T* m_Ptr;
    };



	struct RefCounter
	{
		uint32_t m_RefCount = 0;
		uint32_t m_WeakCount = 0;
	};

	template<typename T>
	class VORTEX_API Ref
	{
	public:
	    Ref()
		{
		    m_Ptr = nullptr;
			m_RefCounter = nullptr;
	    }

		Ref(T* ptr, RefCounter* refCounter = nullptr)
		{
			m_Ptr = ptr;
			m_RefCounter = refCounter;

			++m_RefCounter->m_RefCount;
		}

		Ref(const Ref<T>& ref)
		{
			*this = ref;
			++m_RefCounter->m_RefCount;

			#ifdef REF_COUNTER_DEBUG
			VORTEX_APP_INFO("Ref<{0}> Assign: {1}", typeid(T).name(), m_RefCounter->m_RefCount);
			#endif
		}

		template<std::derived_from<T> From>
		Ref(const Ref<From>& ref)
		{
            *this = ref;
			++m_RefCounter->m_RefCount;

			#ifdef REF_COUNTER_DEBUG
			VORTEX_APP_INFO("Ref<{0}> Assign Derived: {1}", typeid(T).name(), m_RefCounter->m_RefCount);
			#endif
		}

		~Ref()
		{
			if(!m_Ptr && !m_RefCounter)
				return;

			if(!--m_RefCounter->m_RefCount)
			{
				delete m_Ptr;

			    if(!m_RefCounter->m_WeakCount)
					delete m_RefCounter;

				return;
			}

			#ifdef REF_COUNTER_DEBUG
			VORTEX_APP_INFO("Ref<{0}> destruct: {1}", typeid(T).name(), m_RefCounter->m_RefCount);
			#endif
		}

		inline explicit operator bool() const { return m_Ptr; }

		//Copy operator
		template<std::derived_from<T> From>
		Ref<T>& operator=(const Ref<From>& other)
		{
            if(*this == other)
				return *this;

			this->m_Ptr = other.Get();
			this->m_RefCounter = other.GetRefCounter();
			++this->m_RefCounter->m_RefCount;

			#ifdef REF_COUNTER_DEBUG
			VORTEX_APP_INFO("Ref<{0}> Copy: {1}", typeid(From).name(), m_RefCounter->m_RefCount);
			#endif

			return *this;
		}

		//Move operator
		template<std::derived_from<T> From>
		Ref<T>& operator=(const Ref<From>&& other)
		{
		    if(*this == other)
			return *this;

			this->m_Ptr = other.Get();
			this->m_RefCounter = other.GetRefCounter();

			++this->m_RefCounter->m_RefCount;

			#ifdef REF_COUNTER_DEBUG
			VORTEX_APP_INFO("Ref<{0}> Move: {1}", typeid(From).name(), m_RefCounter->m_RefCount);
			#endif

			return *this;
	    }

		template<std::derived_from<T> From>
		bool operator== (const Ref<From>& from)
		{
			return m_Ptr == from.Get();
		}

	public:
		inline T* Get() const { return m_Ptr; }
		inline T* operator ->() const { return m_Ptr; }
		inline T& operator *() const { return *m_Ptr; }

		inline RefCounter* GetRefCounter() const { return m_RefCounter; }

	private:
		T* m_Ptr;
		RefCounter* m_RefCounter;
	};

	template<typename T>
	class VORTEX_API Weak
	{
	public:
	    Weak()
		{
		    m_Ptr = nullptr;
			m_RefCounter = nullptr;
	    }
	    Weak(T* ptr, RefCounter* refCounter)
		{
            m_Ptr = ptr;
			m_RefCounter = refCounter;

			++m_RefCounter->m_WeakCount;
        }
		Weak(Weak<T>&& wptr)
		{
            m_Ptr = wptr.m_Ptr;
			m_RefCounter = wptr.m_RefCounter;

			++m_RefCounter->m_WeakCount;
        }

		~Weak()
		{
            --m_RefCounter->m_WeakCount;

			if(!m_RefCounter->m_RefCount)
				delete m_RefCounter;
		}

        inline explicit operator bool() const { return m_Ptr; }

		Weak<T>& operator=(Weak<T>&& wptr)
		{
            if (*this == wptr) return *this;
            m_Ptr = wptr.m_Ptr;
            return *this;
        }

		//template<std::derived_from<T> From>
		bool operator==(const Weak<T>& wptr)
		{
		    return m_Ptr == wptr.Get();
	    }

		inline T* Get() const { return m_Ptr; }
		inline T* operator ->() const { return m_Ptr; }
		inline T& operator *() const { return *m_Ptr; }
	private:
	    T* m_Ptr;
		RefCounter* m_RefCounter;
    };

	template<typename T, typename... Args>
	constexpr Unique<T> MakeUnique(Args&&... args)
	{
		T* ptr = new T(std::forward<Args>(args)...);

		return Unique<T>(ptr);
	}

	template<typename T, typename... Args>
	constexpr Ref<T> MakeRef(Args&&... args)
	{
		T* ptr = new T(std::forward<Args>(args)...);

		return Ref<T>(ptr, new RefCounter());
	}

	template<typename T>
	constexpr Weak<T> MakeWeak(Ref<T> rptr)
	{
		return Weak<T>(rptr.Get(), rptr.GetRefCounter());
	}
}
