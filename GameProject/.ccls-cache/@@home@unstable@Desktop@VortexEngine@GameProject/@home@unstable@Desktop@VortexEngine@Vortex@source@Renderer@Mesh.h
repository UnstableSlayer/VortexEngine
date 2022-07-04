#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Renderer/Buffers.h"

namespace Vortex
{
	class VORTEX_API Mesh
	{
	public:
		virtual ~Mesh() = default;
		void Load(const std::string& path);

		Ref<VertexArray> m_Data;
	};
}
