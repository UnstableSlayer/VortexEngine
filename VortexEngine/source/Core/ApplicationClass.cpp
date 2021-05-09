#include "vpch.h"

#include "ApplicationClass.h"

#include "Core/Input.h"
#include "Core/Logger.h"

#include "Renderer/Renderer.h"

namespace Vortex
{
	ApplicationClass* ApplicationClass::s_Instance = nullptr;

	ApplicationClass::ApplicationClass() : m_Camera(-1.f, 1.f, -1.f, 1.f)
	{
		s_Instance = this;

		
	}

	ApplicationClass::~ApplicationClass()
	{

	}

	void ApplicationClass::OnStart()
	{
		
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