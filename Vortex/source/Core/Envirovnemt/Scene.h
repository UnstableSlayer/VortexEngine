#pragma once
#include "../Core.h"
#include "../Logger.h"
#include "../Assert.h"

#include "Object.h"

#include <entt/entt.hpp>

namespace Vortex
{
	class Scene
	{
	public:

		Object& CreateObject()
		{
			return Object((uint32_t)m_Registry.create(), &m_Registry);
		}

		template <typename T>
		Object& GetObjectsByComponent()
		{
			auto& view = m_Registry.view<T>();
			Object objects[view.size()];

			for (int i = 0; i < view.size(); i++;)
			{
				objects[i] = Object(view[i]);
			}

			return objects;
		}

		void RemoveObject(uint32_t objectID)
		{
			m_Registry.destroy((entt::entity)objectID);
		}

		void Clear()
		{
			m_Registry.clear();
		}

		size_t size() { return m_Registry.size(); }

		Scope<Object> operator[] (int i)
		{
			return std::make_unique<Object>(Object((uint32_t) * (m_Registry.data() + i), &m_Registry));
		}

	private:
		entt::registry m_Registry;

		friend class Object;
	};
}