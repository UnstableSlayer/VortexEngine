#pragma once
#include <string>
#include <sstream>
#include <functional>
#include <chrono>

#include <VortexEngine.h>

#include "CustomScene.h"

namespace Vortex
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();

		void Input();

		virtual void OnUpdate() override;

		virtual void OnEvent(Event& event) override;
		virtual void OnImGuiRender() override;

	private:
		CustomScene m_Scene;
		Vortex::Object m_Camera;

		std::vector<ProfileResult> m_ProfileResults;
		Ref<Framebuffer> m_ViewportFramebuffer;

		glm::vec4 m_Color = glm::vec4(1.f);

        std::unordered_map<char, Vortex::Ref<Vortex::SubTexture2D>> m_TextureMap;
        const char* m_TileMap;

        Vortex::Ref<Vortex::Mesh> m_ShipMesh;
        Vortex::Ref<Vortex::VertexArray> m_ShipVao;
        Vortex::Ref<Vortex::Shader> m_ShipShader;
        Vortex::Ref<Vortex::Texture2D> m_ShipTexture;
	};
}
