#pragma once
#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/WindowEvents.h"

#include "../ImGui/ImGuiLayer.h"

#include "Renderer/Shader.h"
#include "Renderer/Buffers.h"
#include "Renderer/OrthographicCamera.h"

namespace Vortex
{
	class VORTEX_API ApplicationClass
	{
	public:
		ApplicationClass();
		~ApplicationClass();

		virtual void OnStart();
		virtual void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static ApplicationClass& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		
		virtual bool OnWindowClose(WindowCloseEvent& event);

	protected:

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		bool m_Running = true;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		OrthographicCamera m_Camera;

	private:
		static ApplicationClass* s_Instance;
	};

	//To be defined in game application
	ApplicationClass* CreateApplication();
}