#include "ExampleLayer.h"

class GameApplication : public Vortex::ApplicationClass
{
public:
	GameApplication()
	{
		m_Window = std::unique_ptr<Vortex::Window>(Vortex::Window::Create(Vortex::WindowProperties("Vortex Engine Example Window", 320, 180)));
		m_Window->SetEventCallback(VORTEX_BIND_EVENT(ApplicationClass::OnEvent));
		m_Window->SetVSync(false);

		PushLayer(new ExampleLayer());

		m_ImGuiLayer = new Vortex::ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	~GameApplication() {}

	virtual void OnUpdate() override
	{
		for (Vortex::Layer* layer : m_LayerStack)
			layer->OnUpdate();

		m_ImGuiLayer->Begin();
		for (Vortex::Layer* layer : m_LayerStack)
			layer->OnImGuiRender();
		m_ImGuiLayer->End();

		m_Window->OnUpdate();
	}

	virtual void OnStart() override {}
};

Vortex::ApplicationClass* Vortex::CreateApplication()
{
	VORTEX_CORE_INFO("Initializating Engine Logger...OK");
	VORTEX_APP_INFO("Initializating Application Logger...OK");

	return new GameApplication();
}

