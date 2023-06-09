#include "EditorLayer.h"
#include "EntryPoint.h"

class VortexEditor : public Vortex::App
{
public:
	VortexEditor()
	{
		m_Window = Vortex::Window::Create(Vortex::WindowProperties("Vortex Engine Example Window", 640, 360));
		m_Window->SetEventCallback(VORTEX_BIND_EVENT(App::OnEvent));
		
        m_Window->SetVSync(true);
		m_Window->LockCursor(true);
		PushLayer(new EditorLayer());
		m_ImGuiLayer = new Vortex::ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	~VortexEditor() {}

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

Vortex::App* Vortex::CreateApplication()
{
	return new VortexEditor();
}

