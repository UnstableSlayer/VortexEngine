#include "vpch.h"
#include "OpenGLContext.h"

namespace Vortex
{
	OpenGLContext::OpenGLContext(SDL_Window* hwindow) : m_hWindow(hwindow)
	{

	}

	void OpenGLContext::Init()
	{
		m_Context = SDL_GL_CreateContext(m_hWindow);
		VORTEX_ASSERT(m_Context != NULL, "SDL Context failed to initialise: ");
		VORTEX_CORE_ERROR(SDL_GetError());

		SDL_GL_MakeCurrent(m_hWindow, m_Context);
		int status = gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);
	}

	void OpenGLContext::SwapBuffers()
	{
		SDL_GL_SwapWindow(m_hWindow);
	}

	void OpenGLContext::Destroy()
	{
		SDL_GL_DeleteContext(m_Context);
	}
}
