#include "vpch.h"
#include "App.h"

#include "Input/Input.h"
#include "Core/Logger.h"

//#include "Renderer/RenderCommand.h"
//#include "Renderer/Renderer2D.h"
//#include "Renderer/Renderer3D.h"
#include "Jobs/JobScheduler.h"

namespace Vortex
{
	App* App::s_Instance = nullptr;

	App::App()
	{
		s_Instance = this;
	}

	App::~App()
	{

	}

	void App::OnCreate()
	{
		Time::Init();
		JobScheduler::Init();
		//RenderCommand::Init();
		//Renderer2D::Init();
		//Renderer3D::Init();

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

		JobScheduler::Destroy();
	}

	void App::OnClose()
	{
		m_Running = false;
	}

	void App::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(VORTEX_BIND_EVENT(App::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(VORTEX_BIND_EVENT(App::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (event.m_Handled)
				break;

			(*it)->OnEvent(event);
			//VORTEX_CORE_INFO("Event: {0} {1}", event.ToString(), event.m_Handled);
		}
	}

	void App::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void App::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	bool App::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}

	bool App::OnWindowResize(WindowResizeEvent& event)
	{
		if (event.GetWidth() == 0 || event.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;

		//RenderCommand::SetViewport(0, 0, event.GetWidth(), event.GetHeight());
		//Renderer2D::GetRendererFramebuffer()->Resize({event.GetWidth() / m_Window->GetPixelWidth(), event.GetHeight() / m_Window->GetPixelHeight()});

		return false;
	}
}
