#pragma once
#include "Renderer/Texture.h"
#include "Renderer/Framebuffer.h"

#include "Environment/Components.h"

namespace Vortex
{
	class VORTEX_API Renderer3D
	{
	public:
		static void Init();
		static void Destroy();

		static void BeginScene(CameraComponent& camera, TransformComponent& transform);
		static void EndScene();
		static void EndSceneAndRenderToFramebuffer(Ref<Framebuffer>& targetFB);

		static Ref<Framebuffer>& GetRendererFramebuffer();

		static void DrawMesh(TransformComponent& transform, StaticMeshComponent& staticMesh);

	private:
		static bool IsOutsideOfViewport(TransformComponent& transform);
	};
}
