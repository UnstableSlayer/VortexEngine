#pragma once
#include <string>
#include <functional>
#include <chrono>

#include <VortexEngine.h>

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
		Vortex::Scene m_Scene;
		Vortex::OrthographicCamera m_Camera;

		std::vector<ProfileResult> m_ProfileResults;
		Ref<TransformComponent> transformComp;
		Ref<Framebuffer> m_ViewportFramebuffer;

		glm::vec4 color = glm::vec4(1.f);
	};
}