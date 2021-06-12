#include "vpch.h"

#include "ApplicationClass.h"

#include "Core/Input.h"
#include "Core/Logger.h"

#include "Renderer/Renderer.h"

namespace Vortex
{
	ApplicationClass* ApplicationClass::s_Instance = nullptr;

	ApplicationClass::ApplicationClass()
	{
		s_Instance = this;
		Time::Init();
	}

	ApplicationClass::~ApplicationClass()
	{

	}

	void ApplicationClass::OnCreate()
	{
		Renderer::Init();
		OnStart();

		while (m_Running)
		{
			Timer timer = Timer("DeltaTime", [&](ProfileResult profileReport) {Time::Set(profileReport.Time / 1000.f); });
			OnUpdate();

			if (!m_Minimized)
			{
				for (Vortex::Layer* layer : m_LayerStack)
					layer->OnUpdate();
			}
		}
	}

	void ApplicationClass::OnClose()
	{
		m_Running = false;
	}

	void ApplicationClass::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(VORTEX_BIND_EVENT(ApplicationClass::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(VORTEX_BIND_EVENT(ApplicationClass::OnWindowResize));

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

	bool ApplicationClass::OnWindowResize(WindowResizeEvent& event)
	{
		if (event.GetWidth() == 0 || event.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;

		Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

		return false;
	}
}