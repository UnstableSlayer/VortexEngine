#include "RenderLayer.h"
#include "Environment/ComponentModifiers.h"
#include "Environment/Components.h"
#include "Input/Input.h"
#include "Input/KeyDefs.h"
#include "Renderer/Renderer3D.h"

RenderLayer::RenderLayer() : Layer("RenderLayer")
{
}

void RenderLayer::OnUpdate()
{
    auto camera = Vortex::SCENE->GetObjectWithComponents<Vortex::CameraComponent>();
    
    Vortex::Renderer3D::BeginScene(camera.GetComponent<Vortex::CameraComponent>(), camera.GetComponent<Vortex::TransformComponent>()); 
    Vortex::RenderCommand::Clear(); //{204.f / 255.f, 51.f / 255.f, 0.f, 1.f}
    Vortex::SCENE->Update(camera.GetComponent<Vortex::TransformComponent>().m_Position, Vortex::Time::GetDeltaTime());

    Vortex::Renderer3D::EndScene(); 
}	
