#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/WindowEvents.h"
#include "../ImGui/ImGuiLayer.h"

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

		inline static ApplicationClass& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		bool m_Running = true;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

	private:
		static ApplicationClass* s_Instance;
	};

	//To be defined in game application
	ApplicationClass* CreateApplication();
}