#pragma once
#include "Texture.h"

namespace Vortex
{
	class VORTEX_API SubTexture2D
	{
	public:
		SubTexture2D(const Ref<Texture2D>& atlasTexture, const glm::vec2& min, const glm::vec2& max, const glm::vec2& spriteScale = {1.f, 1.f});

		const Ref<Texture2D>& GetAtlasTexture() { return m_AtlasTexture; }
		const glm::vec2* GetTexCoords() { return m_TexCoords; }
		const glm::vec2& GetSpriteScale() { return m_SpriteScale; }

		static Ref<SubTexture2D> CreateFromPos(const Ref<Texture2D>& atlasTexture, const glm::vec2& spritePos, const glm::vec2& cellSize, const glm::vec2& spriteScale = { 1.f, 1.f });

	private:
		Ref<Texture2D> m_AtlasTexture;
		glm::vec2 m_TexCoords[4];

		glm::vec2 m_SpriteScale;
	};
}