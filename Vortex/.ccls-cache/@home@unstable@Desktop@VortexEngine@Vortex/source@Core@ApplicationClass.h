#pragma once
#include "Core/Window.h"
#include "Core/LayerStack.h"
#include "Events/Event.h"
#include "Events/WindowEvents.h"

#include "ImGui/ImGuiLayer.h"

#include "Renderer/Shader.h"
#include "Renderer/Buffers.h"

#include "Core/Time.h"

namespace Vortex
{
	class VORTEX_API ApplicationClass
	{
	public:
		ApplicationClass();
		~ApplicationClass();

		void OnCreate();
		void OnClose();

		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static ApplicationClass& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		inline ImGuiLayer* GetImGuiLayer() { return  m_ImGuiLayer; }
		
		virtual bool OnWindowClose(WindowCloseEvent& event);
		virtual bool OnWindowResize(WindowResizeEvent& event);

	protected:
		Ref<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		bool m_Running = true;
		bool m_Minimized = false;

	private:
		static ApplicationClass* s_Instance;
	};

	ApplicationClass* CreateApplication();
}
