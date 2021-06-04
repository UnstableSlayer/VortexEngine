#include "VortexEditor.h"

namespace Vortex
{
	VortexEditor::VortexEditor()
	{
		m_Window = std::unique_ptr<Window>(Window::Create(Vortex::WindowProperties("Vortex Engine Example Window", 640, 360)));
		m_Window->SetEventCallback(VORTEX_BIND_EVENT(ApplicationClass::OnEvent));
		m_Window->SetVSync(false);

		PushLayer(new EditorLayer());

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	VortexEditor::~VortexEditor() {}

	void VortexEditor::OnStart() {}

	void VortexEditor::OnUpdate()
	{
		for (Layer* layer : m_LayerStack)
			layer->OnUpdate();

		m_ImGuiLayer->Begin();
		for (Layer* layer : m_LayerStack)
			layer->OnImGuiRender();
		m_ImGuiLayer->End();

		m_Window->OnUpdate();
	}
}