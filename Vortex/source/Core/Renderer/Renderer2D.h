#pragma once
#include "Camera.h"
#include "Texture.h"
#include "../Envirovnemt/Components.h"

namespace Vortex
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Destroy();
		
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		static void DrawQuad(TransformComponent& transform, const glm::vec4& color);
		static void DrawQuad(TransformComponent& transform, const Ref<Texture2D>& texture, const glm::vec2& textureScale = glm::vec2(1.f), const glm::vec4& tint = glm::vec4(1.f));
		static void DrawFromSpriteSheet(TransformComponent& transform, const Texture2D& spriteSheet, const glm::vec2 spriteSize, const glm::vec2 spriteCoord, const glm::vec4& tint = glm::vec4(1.f));
	
	private:
		static void FlushAndReset();



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