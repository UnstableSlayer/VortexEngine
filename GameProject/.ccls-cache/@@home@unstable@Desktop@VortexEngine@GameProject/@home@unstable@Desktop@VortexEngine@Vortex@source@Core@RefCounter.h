#pragma once

namespace Vortex
{
	template<typename T>
	class VORTEX_API Ref
	{
	public:
		Ref()
		{
			m_Ptr = nullptr;
			m_RefCount = nullptr;
		}
		Ref(T* ptr, uint32_t* refCount = nullptr)
		{
			m_Ptr = ptr;
			m_RefCount = refCount ? refCount : new uint32_t(1);
		}

		template<std::derived_from<T> From>
		Ref(const Ref<From>& ref)
		{
			*this = ref;
			++*m_RefCount;
		}

		~Ref()
		{
			if (m_Ptr && !(*m_RefCount))
			{
				if(!--*m_RefCount)
					delete m_Ptr;
					delete m_RefCount;
			}
		}

		inline explicit operator bool() const { return m_Ptr; }

		template<std::derived_from<T> From>
		Ref<T>& operator=(const Ref<From>& other)
		{
			if (*this == other)
				return *this;

			m_Ptr = other.Get();
			m_RefCount = other.GetRefCount();

			++*m_RefCount;

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

		inline uint32_t* GetRefCount() const { return m_RefCount; }

	private:
		T* m_Ptr;
		uint32_t* m_RefCount;
	};

	template<typename T, typename... Args>
	constexpr Ref<T> MakeRef(Args&&... args)
	{
		T* ptr = new T(std::forward<Args>(args)...);

		return Ref<T>(ptr);
	}
}