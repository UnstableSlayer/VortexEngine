#pragma once
#include <entt/entt.hpp>
#include <tuple>

namespace Vortex
{
	using Registry = entt::registry;

	class VORTEX_API Object
	{
	public:
		Object() {}
		Object(uint32_t ID, Registry* registry) : m_ID(ID), m_Registry(registry) {}

		const uint32_t& GetID() { return m_ID; }

		template<typename... T>
		bool HasComponent()
		{
			return m_Registry->all_of<T...>((entt::entity)m_ID);
		}

		template<typename T>
		T& GetComponent()
		{
			return m_Registry->get<T>((entt::entity)m_ID);
		}

		template<typename... T>
		const std::tuple<T...>& GetComponents()
		{
			//if (!HasComponent<T...>()) return *(T*)nullptr;

			return m_Registry->get<T...>((entt::entity)m_ID);
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			//VORTEX_CORE_INFO("Entity({0}) Added componnent {1}", m_ID, typeid(T).name());
			return m_Registry->emplace<T>((entt::entity)m_ID, std::forward<Args>(args)...);
		}

		template<typename T, typename... Args>
		void ReplaceComponent(Args&&... args){
			m_Registry->replace<T>((entt::entity)m_ID, args...);
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
