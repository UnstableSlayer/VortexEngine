#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Buffers.h"

namespace Vortex
{
	class Mesh
	{
	public:
		virtual ~Mesh() = default;
		void Load(const std::string& path);

		Ref<VertexBuffer> m_Vertices;
		Ref<IndexBuffer> m_Indices;
	};
}
