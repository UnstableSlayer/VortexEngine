#pragma once
#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/WindowEvents.h"

#include "../ImGui/ImGuiLayer.h"

#include "Renderer/Shader.h"
#include "Renderer/Buffers.h"
#include "Renderer/Camera.h"

#include "Time.h"

namespace Vortex
{
	class VORTEX_API ApplicationClass
	{
	public:
		ApplicationClass();
		~ApplicationClass();

		void OnCreate();
		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static ApplicationClass& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		
		virtual bool OnWindowClose(WindowCloseEvent& event);
		virtual bool OnWindowResize(WindowResizeEvent& event);

	protected:

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		bool m_Running = true;
		bool m_Minimized = false;

	    Scope<Time> m_Time;

	private:
		static ApplicationClass* s_Instance;
	};

	//To be defined in game application
	ApplicationClass* CreateApplication();
}