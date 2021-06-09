#pragma once
#include <entt/entt.hpp>
#include <tuple>

namespace Vortex
{
	using Registry = entt::registry;

	class Object
	{
	public:
		Object() {}
		Object(uint32_t ID, Registry* registry) : m_ID(ID), m_Registry(registry) {}

		template<typename... T>
		bool HasComponent()
		{
			return m_Registry->all_of<T...>((entt::entity)m_ID);
		}

		template<typename T>
		T& GetComponent()
		{
			return HasComponent<T>() ? m_Registry->get<T>((entt::entity)m_ID) : *(T*)nullptr;
		}

		template<typename... T>
		std::tuple<>& GetComponents()
		{
			if (!HasComponent<T...>()) return *(T*)nullptr;

			auto& [Components] = m_Registry->get<T...>((entt::entity)m_ID);
			return std::make_tuple<T...>(Components);
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return m_Registry->emplace<T>((entt::entity)m_ID, std::forward<Args>(args)...);
		}

		template<typename T>
		void RemoveComponent()
		{
			if (HasComponent<T>())
				m_Registry->remove<T>(m_ID);
		}

		operator bool() const { return m_ID != entt::null; }

	public:
		uint32_t m_ID = entt::null;

	private:
		Registry* m_Registry = nullptr;
	};
}