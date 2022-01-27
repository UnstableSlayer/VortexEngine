#pragma once
#include "Environment/Object.h"

#include <entt/entt.hpp>
#include <glm/glm.hpp>

namespace Vortex
{
	class VORTEX_API Scene
	{
	public:
		virtual void Update(const glm::vec3& cameraPos, const float DeltaTime);

		Object& CreateObject()
		{
			uint32_t id = (uint32_t)m_Registry.create();
			Object* obj = new Object(id, &m_Registry);
			return *obj;
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
		Object* operator[] (int i)
		{
			currentObject->m_ID = (uint32_t)*m_Registry.data() + i;
			return currentObject;
		}

	private:
		entt::registry m_Registry = entt::registry();
		Object* currentObject = new Object(entt::null, &m_Registry);

		friend class Object;
	};
}
