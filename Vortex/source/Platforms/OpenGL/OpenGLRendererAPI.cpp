#include "vpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/gl.h>

namespace Vortex
{
	void OpenGLRendererAPI::Init()
	{
		VORTEX_CORE_INFO("OpenGL Init:");
		VORTEX_CORE_INFO("	-Version: {0}", glGetString(GL_VERSION));
		VORTEX_CORE_INFO("	-Vendor: {0}", glGetString(GL_VENDOR));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        	glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
        	glDepthFunc(GL_LESS);

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		//glFrontFace(GL_CCW);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::Clear(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	void OpenGLRendererAPI::DrawIndexed(Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
