#include "vpch.h"
#include "RenderCommand.h"

#include "Platforms/OpenGL/OpenGLRendererAPI.h"

namespace Vortex
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}