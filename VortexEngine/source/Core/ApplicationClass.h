#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/WindowEvents.h"

namespace Vortex
{
	class VORTEX_API ApplicationClass
	{
	public:
		ApplicationClass();
		~ApplicationClass();

		void OnStart();
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;
	};

	//To be defined in game application
	ApplicationClass* CreateApplication();
}