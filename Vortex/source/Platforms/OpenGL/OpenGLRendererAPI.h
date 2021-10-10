#pragma once
#include "Core/Renderer/RendererAPI.h"

namespace Vortex
{
	class VORTEX_API OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void Clear(const glm::vec4& color = glm::vec4()) override;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
	};
}
