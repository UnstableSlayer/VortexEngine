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

		static void DrawQuad(TransformComponent& transform, const glm::vec4& color);
		static void DrawQuad(TransformComponent& transform, const Texture2D& texture, const glm::vec2& textureScale = glm::vec2(1.f), const glm::vec4& tint = glm::vec4(1.f));
	};
}