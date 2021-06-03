#pragma once
#include "Core/Core.h"
#include "Texture.h"

namespace Vortex
{
	class SubTexture2D
	{
	public:
		SubTexture2D(const Ref<Texture2D>& atlasTexture, const glm::vec2& min, const glm::vec2& max);

		const Ref<Texture2D>& GetAtlasTexture() { return m_AtlasTexture; }
		const glm::vec2* GetTexCoords() { return m_TexCoords; }

		static Ref<SubTexture2D> CreateFromPos(const Ref<Texture2D>& atlasTexture, const glm::vec2& spritePos, const glm::vec2& cellSize, const glm::vec2& spriteSize = { 1.f, 1.f });

	private:
		Ref<Texture2D> m_AtlasTexture;
		glm::vec2 m_TexCoords[4];
	};
}