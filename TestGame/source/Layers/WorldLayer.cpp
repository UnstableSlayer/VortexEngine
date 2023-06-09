#include "WorldLayer.h"
#include "Environment/ComponentModifiers.h"
#include "Environment/Components.h"

WorldLayer::WorldLayer() : Layer("WorldLayer")
{
    float radius = 15.f;
    uint32_t count = 16;

    auto texture = Vortex::Texture2D::Create("Textures/Ball.png", Vortex::TextureFormat::RGBA8);

    for (size_t x = 0; x < count; x++)
    {
        for (size_t y = 0; y < count; y++)
        {
            Vortex::Object obj = Vortex::SCENE->CreateObject();
            //obj.AddComponent<Vortex::TagComponent>("Ball");
            Vortex::TransformComponent& transform = obj.AddComponent<Vortex::TransformComponent>();
            float angleX = ((360.f / (count)) * x);
            float angleY = ((360.f / (count)) * y);
            Vortex::Transform::SetPosition(transform, { radius * cosf(angleX) * sinf(angleY) + 0.001f * x,
                                                        radius * sinf(angleX) * sinf(angleY) + 0.001f * y,
                                                        radius * cosf(angleY) + 0.0001f * y * x });

            auto& renderer2DComponent = obj.AddComponent<Vortex::SpriteComponent>();
            renderer2DComponent.m_Texture = texture;

           // float a = abs(sinf(x)), b = abs(cosf(y));
           // renderer2DComponent.m_Tint = { a, 0.f, a + b, 1.f };
        }
    }
}

void WorldLayer::OnUpdate()
{
    
}

void WorldLayer::OnImGuiRender(){
    ImGui::Begin("World");
    
    ImGui::End();
}
