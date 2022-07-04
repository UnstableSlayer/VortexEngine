#include "vpch.h"
#include "ApplicationClass.h"

#include "Core/Input.h"
#include "Core/Logger.h"

#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer2D.h"
#include "Jobs/JobScheduler.h"

namespace Vortex
{
	ApplicationClass* ApplicationClass::s_Instance = nullptr;

	ApplicationClass::ApplicationClass()
	{
		s_Instance = this;
	}

	ApplicationClass::~ApplicationClass()
	{

	}

	void ApplicationClass::OnCreate()
	{
		Time::Init();
		//JobScheduler::Init();
		RenderCommand::Init();
		Renderer2D::Init();

		OnStart();

		while (m_Running)
		{
			Timer timer = Timer("DeltaTime", [&](ProfileResult profileReport) { Time::Set(profileReport.Time); });
			OnUpdate();

			if (!m_Minimized)
			{
				for (Vortex::Layer* layer : m_LayerStack)
					layer->OnUpdate();
			}
		}

		//JobScheduler::Destroy();
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

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (event.m_Handled)
				break;

			(*it)->OnEvent(event);
			//VORTEX_CORE_INFO("Event: {0} {1}", event.ToString(), event.m_Handled);
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

		RenderCommand::SetViewport(0, 0, event.GetWidth(), event.GetHeight());

		return false;
	}
}
