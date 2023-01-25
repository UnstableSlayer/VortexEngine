#include "TestGame.h"

#include "Core/Layer.h"
#include "CustomScene.h"

#include "ImGui/ImGuiLayer.h"
#include "Layers/PlayerLayer.h"
#include "Layers/RenderLayer.h"
#include "Layers/WorldLayer.h"

TestGame::TestGame()
{
    m_Window = Vortex::Window::Create(Vortex::WindowProperties("Vortex Engine Example Window", 1280, 720, 1, 1));
    m_Window->SetEventCallback(VORTEX_BIND_EVENT(App::OnEvent));

    m_Window->SetVSync(false);
	m_Window->LockCursor(false);

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

    PushLayer(new PlayerLayer());
    PushLayer(new WorldLayer());
    PushLayer(new RenderLayer());
    m_ImGuiLayer = new Vortex::ImGuiLayer();
    PushOverlay(m_ImGuiLayer);
}

TestGame::~TestGame() {}

void TestGame::OnStart() {}

void TestGame::OnUpdate()
{
    //VORTEX_APP_INFO("Memory allocated: {0} KB", (float)(Vortex::Allocator::m_MemoryHead - Vortex::Allocator::m_Memory) / 1024);

    for (Vortex::Layer* layer : m_LayerStack)
		layer->OnUpdate();

    m_ImGuiLayer->Begin();

	for (Vortex::Layer* layer : m_LayerStack)
        layer->OnImGuiRender();
	m_ImGuiLayer->End();

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
