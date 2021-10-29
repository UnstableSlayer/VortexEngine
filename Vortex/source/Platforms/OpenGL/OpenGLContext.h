#pragma once
#include "Core/Renderer/GraphicsContext.h"

#include <glad/gl.h>
#include <SDL2/SDL.h>

namespace Vortex
{
	class VORTEX_API OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(SDL_Window* hwindow);

		virtual void Init() override;
		virtual void SwapBuffers() override;
		virtual void Destroy() override;
	private:
		SDL_Window* m_hWindow;
		SDL_GLContext m_Context;
	};
}
