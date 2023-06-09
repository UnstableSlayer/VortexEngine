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

                glm::vec3 direction = transform.m_Position - cameraPos;
                Vortex::Transform::Rotate(transform, glm::normalize(direction));

                Renderer2D::DrawQuad(transform, sprite, sprite.m_Tint);
			}
		}

       /*{
            auto view = m_Registry.view<TransformComponent, StaticMeshComponent>();
            auto res = view.use<TransformComponent>();
            for (auto [entity, transform, staticMesh] : view.each())
            {
                //RNG::m_Seed = 64;
                //Transform::Rotate(transform, glm::vec3(RNG::RandFloat(), RNG::RandFloat(), RNG::RandFloat()) * 10.f * Time::GetDeltaTime());
                Renderer3D::DrawMesh(transform, staticMesh);
            }
        }*/

        /*{
            auto view = m_Registry.view<TransformComponent, TestGameComponents::PlayerComponent>();
            for (auto [entity, transform, player] : view.each())
            {
                //Vortex::Transform::Move(transform, {player.currentVelocity * Vortex::Time::GetDeltaTime(), 0.f});
                Renderer2D::DrawQuad(player.headTransform, player.tankHead, player.tankHead.m_Tint);
                Renderer2D::DrawQuad(transform, player.tankBody, player.tankBody.m_Tint);
            }
        }*/
    }
};
