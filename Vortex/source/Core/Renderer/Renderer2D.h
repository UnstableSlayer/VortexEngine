#pragma once
#include "Camera.h"
#include "Texture.h"
#include "SubTexture2D.h"
#include "../Envirovnemt/Components.h"

namespace Vortex
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Destroy();
		
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		static void DrawQuad(TransformComponent& transform, const glm::vec4& color);
		static void DrawQuad(TransformComponent& transform, const Ref<Texture2D>& texture, const glm::vec2& textureScale = glm::vec2(1.f), const glm::vec4& tint = glm::vec4(1.f));
		static void DrawSubQuad(TransformComponent& transform, const Ref<SubTexture2D>& spriteAtlas, const glm::vec4& tint = glm::vec4(1.f));
		static void DrawFromTileMap(const char* tileMap, const int32_t& mapWidth, const std::unordered_map<char, Ref<SubTexture2D>>& textureMap, const glm::vec4& tint = glm::vec4(1.f));
	
	private:
		static void FlushAndReset();
		static void AppendSingleVertexData(const glm::vec3& position, const glm::vec4& color, const glm::vec2& texCoord, const glm::vec2& texTiling, const float& textureIndex);

		static bool CameraCulling(TransformComponent& transform);

	public:
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetVertexCount() { return QuadCount * 4; }
			uint32_t GetIndexCount() { return QuadCount * 6; }
		};

		static Statistics GetStats();
		static void ResetStats();
	};
}