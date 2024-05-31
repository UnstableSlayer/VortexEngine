#include "PlayerLayer.h"
#include <cstdint>
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

#include "../Components/PlayerComponent.h"
#include "Environment/ComponentModifiers.h"
#include "Environment/Components.h"
#include "Input/Input.h"
#include "Renderer/Texture.h"

PlayerLayer::PlayerLayer() : Layer("PlayerLayer")
{
    //PlayerObj
    {
        m_PlayerObj = Vortex::SCENE->CreateObject();
        auto& transform = m_PlayerObj.AddComponent<Vortex::TransformComponent>();
        auto& bodySprite = m_PlayerObj.AddComponent<Vortex::SpriteComponent>();//, headSprite;
        
        bodySprite.m_Texture = Vortex::Texture2D::Create("Textures/Ball.png", Vortex::TextureFormat::RGBA16);
    }
}

void PlayerLayer::Input()
{
    auto cameraObj = Vortex::SCENE->GetObjectWithComponents<Vortex::CameraComponent>();
    auto& transform = cameraObj.GetComponent<Vortex::TransformComponent>();
    auto& camera = cameraObj.GetComponent<Vortex::CameraComponent>();

    glm::vec3 velocity = glm::vec3(0.f);
    glm::vec3 angularVelocity = glm::vec3(0.f);
    float scale = camera.m_Zoom;

    if (Vortex::Input::IsKeyPressed(Vortex::Key::I)) scale += 10.f * Vortex::Time::GetDeltaTime();
    if (Vortex::Input::IsKeyPressed(Vortex::Key::O)) scale -= 10.f * Vortex::Time::GetDeltaTime();

    if (Vortex::Input::IsKeyPressed(Vortex::Key::S)) velocity.z =  10.f * Vortex::Time::GetDeltaTime();
    if (Vortex::Input::IsKeyPressed(Vortex::Key::W)) velocity.z = -10.f * Vortex::Time::GetDeltaTime();
    if (Vortex::Input::IsKeyPressed(Vortex::Key::A)) velocity.x = -20.f * Vortex::Time::GetDeltaTime();
    if (Vortex::Input::IsKeyPressed(Vortex::Key::D)) velocity.x =  20.f * Vortex::Time::GetDeltaTime();
    if (Vortex::Input::IsKeyPressed(Vortex::Key::Q)) velocity.y = -10.f * Vortex::Time::GetDeltaTime();
    if (Vortex::Input::IsKeyPressed(Vortex::Key::E)) velocity.y =  10.f * Vortex::Time::GetDeltaTime();

    if (Vortex::Input::IsKeyPressed(Vortex::Key::ESC)) Vortex::App::Get().GetWindow().LockCursor(false);
    if (Vortex::Input::IsMouseButtonPressed(Vortex::MouseKey::L)) Vortex::App::Get().GetWindow().LockCursor(true);

    {
        auto [mouseDeltaX, mouseDeltaY] = Vortex::Input::GetMouseDelta();
        {
            float deltaX = mouseDeltaY;
            float deltaY = mouseDeltaX;

            angularVelocity.x = -deltaX / 10.f;
            angularVelocity.y = -deltaY / 10.f;
        }
    }

    Vortex::Transform::Move(transform, transform.m_Rotation * velocity);
    Vortex::Transform::Rotate(transform, glm::normalize(transform.m_Rotation) * angularVelocity);
    Vortex::Camera::PerspectiveZoom(camera, scale);
}

void PlayerLayer::OnUpdate()
{
    Input();
}

void PlayerLayer::OnEvent(Vortex::Event &event)
{

}

void PlayerLayer::OnImGuiRender(){
    ImGui::Begin("Performance");
    static float maxFrameTime = 0.f;
    float deltaTime = Vortex::Time::GetDeltaTime();
    
    if(deltaTime > maxFrameTime)
        maxFrameTime = deltaTime;

    ImGui::Text("FrameTime: %f", deltaTime);
    ImGui::Text("FrameRate: %f", 1.f / deltaTime);
    ImGui::Text("MaxFrameTime: %f", maxFrameTime);
    ImGui::End();

    ImGui::Begin("Camera");
    auto cameraObj = Vortex::SCENE->GetObjectWithComponents<Vortex::CameraComponent>();
    auto& transform = cameraObj.GetComponent<Vortex::TransformComponent>();
    ImGui::InputFloat3("Position", (float*)&transform.m_Position);
    auto& camera = cameraObj.GetComponent<Vortex::CameraComponent>();
    ImGui::InputFloat("Zoom", &camera.m_Zoom);
    Vortex::Camera::OrthographicZoom(camera, camera.m_Zoom);
    ImGui::End();
}
