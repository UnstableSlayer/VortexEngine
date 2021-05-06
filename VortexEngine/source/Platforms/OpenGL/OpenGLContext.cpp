#include "vpch.h"
#include "OpenGLContext.h"

namespace Vortex
{
	OpenGLContext::OpenGLContext(GLFWwindow* hwindow) : m_hWindow(hwindow) 
	{

	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_hWindow);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_hWindow);
	}
}