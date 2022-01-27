#include "vpch.h"
#include "Scene.h"

#include "Environment/Components.h"
#include "Renderer/Renderer2D.h"

namespace Vortex
{
	void Scene::Update(const glm::vec3& cameraPos, const float DeltaTime)
	{
		m_Registry.sort<TransformComponent>([&](const auto& one, const auto& another) {
			return glm::distance(cameraPos, one.GetPosition()) > glm::distance(cameraPos, another.GetPosition());
		});
		
		{
			auto view = m_Registry.view<TransformComponent, SpriteComponent>();
			view.use<TransformComponent>();
			for (auto [entity, transform, sprite] : view.each())
			{
				Renderer2D::DrawQuad(transform, sprite, sprite.m_Tint);
			}
		}

		{
			auto view = m_Registry.view<TransformComponent, SubSpriteComponent>();
			for (auto [entity, transform, subSprite] : view.each())
			{
				Renderer2D::DrawSubQuad(transform, subSprite.m_Sprite, subSprite.m_Tint);
			}
		}
	}
}
