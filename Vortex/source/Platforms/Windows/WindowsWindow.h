#pragma once
#include "Core/Window.h"
#include "Core/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Vortex
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& properties);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline const uint32_t GetWindowWidth() const override { return m_Data.width; }
		inline const uint32_t GetWindowHeight() const override { return m_Data.height; }

		inline void SetEventCallback(const EventCallback& callback) override { m_Data.eventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetAPIWindow() const override
		{
			return m_Window;
		}

	private:
		virtual void Init(const WindowProperties& properties);
		virtual void Close();

	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string title;
			uint32_t width, height;
			bool vSync;

			EventCallback eventCallback;
		};

		WindowData m_Data;
	};
}