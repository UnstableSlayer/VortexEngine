#pragma once
#include "Core/Renderer/GraphicsContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct GLFWwindow;

namespace Vortex
{
	class VORTEX_API OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* hwindow);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_hWindow;
	};
}
