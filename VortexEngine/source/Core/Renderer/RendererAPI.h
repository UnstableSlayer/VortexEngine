#pragma once

#include "Buffers.h"
#include <glm/glm.hpp>

namespace Vortex
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};

	public:
		virtual void Clear(const glm::vec4& color = glm::vec4()) = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}