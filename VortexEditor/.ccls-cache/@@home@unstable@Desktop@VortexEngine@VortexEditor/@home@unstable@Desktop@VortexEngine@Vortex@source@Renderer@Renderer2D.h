#pragma once
#include "Renderer/Texture.h"
#include "Renderer/SubTexture2D.h"
#include "Environment/Object.h"
#include "Environment/Components.h"
#include "Environment/ComponentModifiers.h"
#include "Renderer/Mesh.h"
#include "Renderer/Framebuffer.h"

namespace Vortex
{
	class VORTEX_API Renderer2D
	{
	public:
		static void Init();
		static void Destroy();

		static void BeginScene(Object& cameraObj);
		static void EndScene();
		static void EndSceneAndRenderToFramebuffer(Ref<Framebuffer>& targetFB);
		static void Flush();

		static const Ref<Framebuffer>& GetRendererFramebuffer();

		static void DrawQuad(TransformComponent& transform, const glm::vec4& color);
		static void DrawQuad(TransformComponent& transform, const SpriteComponent& sprite, const glm::vec4& tint = glm::vec4(1.f));
		static void DrawSubQuad(TransformComponent& transform, const Ref<SubTexture2D>& spriteAtlas, const glm::vec4& tint = glm::vec4(1.f));
		static void DrawFromTileMap(const char* tileMap, const uint32_t& mapWidth, const std::unordered_map<char, Ref<SubTexture2D>>& textureMap, const glm::vec4& tint = glm::vec4(1.f));

	private:
		static void FlushAndReset();
		static void AppendSingleVertexData(const glm::vec3& position, const glm::vec4& color, const glm::vec2& texCoord, const glm::vec2& texTiling, const float& textureIndex);

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
