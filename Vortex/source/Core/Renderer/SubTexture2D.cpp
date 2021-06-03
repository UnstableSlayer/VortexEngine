#include "vpch.h"
#include "SubTexture2D.h"

namespace Vortex
{
	SubTexture2D::SubTexture2D(const Ref<Texture2D>& atlasTexture, const glm::vec2& min, const glm::vec2& max)
		: m_AtlasTexture(atlasTexture)
	{
		m_TexCoords[0] = { min.x, min.y };
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };
	}

	Ref<SubTexture2D> SubTexture2D::CreateFromPos(const Ref<Texture2D>& atlasTexture, const glm::vec2& position, const glm::vec2& size)
	{
		const glm::vec2 atlasSize = atlasTexture->GetSize();

		//Reversing y of position to start indexing from top left of atlas
		const glm::vec2 reversePos = { position.x, (atlasTexture->GetSize().y / size.y) - position.y - 1.f };

		const glm::vec2 min = { (reversePos.x * size.x) / atlasSize.x, (reversePos.y * size.y) / atlasSize.y };
		const glm::vec2 max = { ((reversePos.x + 1.f) * size.x) / atlasSize.x, ((reversePos.y + 1.f) * size.y) / atlasSize.y };

		return std::make_shared<SubTexture2D>(SubTexture2D(atlasTexture, min, max));
	}
}