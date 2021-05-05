#include "vpch.h"

#include "ApplicationClass.h"
#include "Logger.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Vortex
{
	ApplicationClass* ApplicationClass::s_Instance = nullptr;

	ApplicationClass::ApplicationClass()
	{
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(VORTEX_BIND_EVENT(ApplicationClass::OnEvent));
	}

	ApplicationClass::~ApplicationClass()
	{

	}

	void ApplicationClass::OnStart()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();

			glClearColor(1.f, 0.f, 0.5f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
		}
	}

	void ApplicationClass::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(VORTEX_BIND_EVENT(ApplicationClass::OnWindowClose));

		for (auto i = m_LayerStack.end(); i != m_LayerStack.begin();)
		{
			(*--i)->OnEvent(event);

			if (event.m_Handled)
				break;
		}
	}

	void ApplicationClass::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void ApplicationClass::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	bool ApplicationClass::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}
}