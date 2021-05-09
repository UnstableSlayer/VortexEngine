#include "vpch.h"
#include "Renderer.h"

namespace Vortex
{
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
	}
	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}