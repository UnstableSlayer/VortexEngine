#include "vpch.h"
#include "SubTexture2D.h"

namespace Vortex
{
	SubTexture2D::SubTexture2D(const Ref<Texture2D>& atlasTexture, const glm::vec2& min, const glm::vec2& max, const glm::vec2& spriteSize)
		: m_AtlasTexture(atlasTexture), m_SpriteScale(spriteSize)
	{
		m_TexCoords[0] = { min.x, min.y };
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };
	}

	Ref<SubTexture2D> SubTexture2D::CreateFromPos(const Ref<Texture2D>& atlasTexture, const glm::vec2& spritePos, const glm::vec2& cellSize, const glm::vec2& spriteScale)
	{
		const glm::vec2 atlasSize = atlasTexture->GetSize();

		const glm::vec2 min = { (spritePos.x * cellSize.x) / atlasSize.x, (spritePos.y * cellSize.y) / atlasSize.y };
		const glm::vec2 max = { ((spritePos.x + spriteScale.x) * cellSize.x) / atlasSize.x, ((spritePos.y + spriteScale.y) * cellSize.y) / atlasSize.y };

		return MakeRef<SubTexture2D>(atlasTexture, min, max, spriteScale);
	}
}