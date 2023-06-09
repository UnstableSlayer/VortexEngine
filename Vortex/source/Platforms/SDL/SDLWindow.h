#pragma once
#include "Core/Window.h"
#include "Renderer/GraphicsContext.h"

#include "SDL.h"

namespace Vortex
{
	class VORTEX_API SDLWindow : public Window
	{
	public:
		SDLWindow(const WindowProperties& properties);
		virtual ~SDLWindow();

		void OnUpdate() override;

		inline const std::string& GetWindowTitle() const override { return m_Data.title; }
		inline uint32_t GetWindowWidth() const override { return m_Data.width; }
		inline uint32_t GetWindowHeight() const override { return m_Data.height; }
		inline uint32_t GetPixelWidth() const override { return m_Data.pixelWidth; }
		inline uint32_t GetPixelHeight() const override { return m_Data.pixelHeight; }
		inline int GetPositionX() const override;
		inline int GetPositionY() const override;

		inline void SetWindowTitle(const std::string& title) override 
		{ 
			m_Data.title = title; 
			SDL_SetWindowTitle(m_Window, title.c_str()); 
		}

		inline void SetEventCallback(const EventCallback& callback) override { m_Data.eventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		void LockCursor(bool enabled) override;

		inline virtual void* GetAPIWindow() const override
		{
			return m_Window;
		}

	private:
		virtual void Init(const WindowProperties& properties);
		virtual void Close();

	private:
		SDL_Window* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string title;
			uint32_t width, height;
			uint32_t pixelWidth, pixelHeight;
			bool vSync;

			EventCallback eventCallback;
		};

		WindowData m_Data;
	};
}
