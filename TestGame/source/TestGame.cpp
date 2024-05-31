#include "TestGame.h"

#include "Core/Layer.h"
#include "CustomScene.h"

#include "Layers/WorldLayer.h"

TestGame::TestGame()
{
    m_Window = Vortex::Window::Create(Vortex::WindowProperties("Vortex Engine Example Window", 1920, 1080, 1, 1));
    m_Window->SetEventCallback(VORTEX_BIND_EVENT(App::OnEvent));

    m_Window->SetVSync(true);
	m_Window->LockCursor(false);
}

TestGame::~TestGame() {}

void TestGame::OnStart() { 
	m_Scene = Vortex::MakeRef<CustomScene>();

	// Camera
    {
        m_Camera = m_Scene->CreateObject();
        auto &transform = m_Camera.AddComponent<Vortex::TransformComponent>();
        Vortex::Transform::SetPosition(transform, {0.f, 0.f, 10.f});

        auto &camera = m_Camera.AddComponent<Vortex::CameraComponent>();
        Vortex::Camera::Init(camera, Vortex::CameraType::Orthographic, 16.f, 9.f, 1.f, 10000.f, 55.f);
        VORTEX_APP_INFO("Camera Initialized!");
    }

    PushLayer(new WorldLayer());
}

void TestGame::OnUpdate()
{
    for (Vortex::Layer* layer : m_LayerStack)
		layer->OnUpdate();

	m_Window->OnUpdate();
}

void TestGame::OnEvent(Vortex::Event &event)
{
    Vortex::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Vortex::WindowResizeEvent>(VORTEX_BIND_EVENT(TestGame::OnCameraResize));

    App::OnEvent(event);
}


bool TestGame::OnCameraResize(Vortex::WindowResizeEvent &event)
{
    Vortex::Camera::OnWindowResize(event, m_Camera.GetComponent<Vortex::CameraComponent>());
    VORTEX_APP_INFO("Window resized to {0}x{1}", event.GetWidth(), event.GetHeight());
    return false;
}
