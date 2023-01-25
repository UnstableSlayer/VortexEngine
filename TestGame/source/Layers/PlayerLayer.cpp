#include "PlayerLayer.h"
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

#include "../Components/PlayerComponent.h"
#include "Environment/ComponentModifiers.h"
#include "Environment/Components.h"
#include "Input/Input.h"

PlayerLayer::PlayerLayer() : Layer("PlayerLayer")
{
    //PlayerObj
    {
        //m_PlayerObj = Vortex::SCENE->CreateObject();
        //auto& transform = m_PlayerObj.AddComponent<Vortex::TransformComponent>();

        //auto& sprite = m_PlayerObj.AddComponent<Vortex::SpriteComponent>();
             //sprite.m_Texture = Vortex::Texture2D::Create("Textures/shipSprite.png");

        //auto& playerComp = m_PlayerObj.AddComponent<TestGameComponents::PlayerComponent>();
              //playerComp.maxVelocity = { 2.f, 2.f };
              //playerComp.acceleration = { 1.f, 1.f };
              //playerComp.drag = {1.5f, 1.5f};
              //playerComp.health = 100.f;
    }
}

void PlayerLayer::Input()
{
    auto cameraObj = Vortex::SCENE->GetObjectWithComponents<Vortex::CameraComponent>();
    auto& transform = cameraObj.GetComponent<Vortex::TransformComponent>();
    auto& camera = cameraObj.GetComponent<Vortex::CameraComponent>();

    //auto& [transform, camera] = cameraObj.GetComponents<Vortex::TransformComponent, Vortex::CameraComponent>();

    glm::vec3 deltaPos = glm::vec3(0.f);
    float zoom = camera.m_Zoom;

    if(Vortex::Input::IsKeyPressed(Vortex::Key::W))
        deltaPos.y += 5.f * Vortex::Time::GetDeltaTime();
    if(Vortex::Input::IsKeyPressed(Vortex::Key::S))
        deltaPos.y -= 5.f * Vortex::Time::GetDeltaTime();
    if(Vortex::Input::IsKeyPressed(Vortex::Key::D))
        deltaPos.x += 5.f * Vortex::Time::GetDeltaTime();
    if(Vortex::Input::IsKeyPressed(Vortex::Key::A))
        deltaPos.x -= 5.f * Vortex::Time::GetDeltaTime();

    if(Vortex::Input::IsKeyPressed(Vortex::Key::I))
        zoom += 0.5f * Vortex::Time::GetDeltaTime();
    if(Vortex::Input::IsKeyPressed(Vortex::Key::O))
        zoom -= 0.5f * Vortex::Time::GetDeltaTime();

    Vortex::Transform::Move(transform, deltaPos);
    Vortex::Camera::OrthographicZoom(camera, zoom);
}

void PlayerLayer::OnUpdate()
{
    Input();
}

void PlayerLayer::OnEvent(Vortex::Event &event)
{

}

void PlayerLayer::OnImGuiRender(){
    ImGui::Begin("Camera");
    auto cameraObj = Vortex::SCENE->GetObjectWithComponents<Vortex::CameraComponent>();
    auto& transform = cameraObj.GetComponent<Vortex::TransformComponent>();
    ImGui::InputFloat3("Position", (float*)&transform.m_Position);
    auto& camera = cameraObj.GetComponent<Vortex::CameraComponent>();
    ImGui::InputFloat("Zoom", &camera.m_Zoom);
    Vortex::Camera::OrthographicZoom(camera, camera.m_Zoom);
    ImGui::End();
}
