#pragma once
#include "Core/Renderer/RendererAPI.h"

namespace Vortex
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Clear(const glm::vec4& color = glm::vec4()) override;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}
