#include "vpch.h"

#include "WindowsWindow.h"
#include "Core/Events/WindowEvents.h"
#include "Core/Events/MouseEvents.h"
#include "Core/Events/KeyEvent.h"

#include "Platforms/OpenGL/OpenGLContext.h"

namespace Vortex
{
	static bool b_SDLInitialized = false;

	Window* Window::Create(const WindowProperties& properties)
	{
		return new WindowsWindow(properties);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		Init(properties);
	}

	WindowsWindow::~WindowsWindow() {}

	void WindowsWindow::Init(const WindowProperties& properties)
	{
		m_Data.title = properties.title;
		m_Data.width = properties.width;
		m_Data.height = properties.height;

		VORTEX_CORE_TRACE("Creating window '{0}' {1}x{2}", properties.title, properties.width, properties.height);

		if (!b_SDLInitialized)
		{
			int result = SDL_Init(SDL_INIT_EVERYTHING);
			SDL_GL_LoadLibrary(NULL);

			SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

			//MaybeToDo: Error handling callback

			b_SDLInitialized = true;
		}

		m_Window = SDL_CreateWindow(m_Data.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			(int)properties.width, (int)properties.height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();
		
		SDL_GetWindowSurface(m_Window)->userdata = &m_Data;
		SetVSync(true);

		SDL_AddEventWatch((SDL_EventFilter)[](void* userdata, SDL_Event* event)
			{
				if (event->type != SDL_WINDOWEVENT || event->window.event != SDL_WINDOWEVENT_RESIZED) return 1;

				WindowData& data = *(WindowData*)userdata;
				data.width = event->window.data1;
				data.height = event->window.data2;

				WindowResizeEvent veEvent(event->window.data1, event->window.data2);
				data.eventCallback(veEvent);

				return 0;
			}, (void*)&m_Data);
		
		SDL_AddEventWatch((SDL_EventFilter)[](void* userdata, SDL_Event* event)
			{
				if (event->type != SDL_WINDOWEVENT || event->window.event != SDL_WINDOWEVENT_CLOSE) return 1;

				WindowData& data = *(WindowData*)userdata;
				WindowCloseEvent veEvent;
				data.eventCallback(veEvent);

				return 0;
			}, (void*)&m_Data);
	}
	 
	void WindowsWindow::Close()
	{
		m_Context->Destroy();
		SDL_DestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		enabled ? SDL_GL_SetSwapInterval(1) : SDL_GL_SetSwapInterval(0);
		m_Data.vSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.vSync;
	}

	void WindowsWindow::LockCursor(bool enable)
	{
		//SDL_SetWindowMouseGrab(m_Window, (SDL_bool)enable);
		int result = SDL_SetRelativeMouseMode((SDL_bool)enable);

		VORTEX_ASSERT(result == 0, "SDL couldn't set relative mouse mode: {0}", SDL_GetError());
	}
}