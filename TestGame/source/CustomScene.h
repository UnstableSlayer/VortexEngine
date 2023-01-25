#include <VortexEngine.h>
#include "Components/PlayerComponent.h"

class CustomScene : public Vortex::Scene
{
public:

    void Update(const glm::vec3& cameraPos, const float DeltaTime) override
    {
        using namespace Vortex;

        m_Registry.sort<TransformComponent>([&](const auto& one, const auto& another) {
			return glm::distance(cameraPos, one.m_Position) > glm::distance(cameraPos, another.m_Position);
		});

        {
			auto view = m_Registry.view<TransformComponent, SpriteComponent>();
			auto res = view.use<TransformComponent>();
			for (auto [entity, transform, sprite] : view.each())
		    {
                if(!sprite.m_Texture)
                {
                    VORTEX_APP_WARNING("Entity with id {0}: SpriteComponent doesn't have a valid Texture", (uint32_t)entity);
                    continue;
                }
                Renderer2D::DrawQuad(transform, sprite, sprite.m_Tint);
			}
		}


        {
            auto view = m_Registry.view<TransformComponent, TestGameComponents::PlayerComponent>();
            for (auto [entity, transform, player] : view.each())
            {
                Vortex::Transform::Move(transform, {player.currentVelocity * Vortex::Time::GetDeltaTime(), 0.f});
            }
        }
    }
};
