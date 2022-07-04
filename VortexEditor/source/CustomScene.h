#include <VortexEngine.h>

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
};
