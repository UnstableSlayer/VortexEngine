#pragma once
#include <string>
#include <functional>
#include <chrono>

#include <VortexEngine.h>

class ExampleLayer : public Vortex::Layer
{
public:
	ExampleLayer();

	void Input();

	virtual void OnUpdate() override;

	virtual void OnEvent(Vortex::Event& event) override;
	virtual void OnImGuiRender() override;

private:
	Vortex::Scene m_Scene;
	Vortex::OrthographicCamera m_Camera;

	std::vector<Vortex::ProfileResult> m_ProfileResults;
	Vortex::Ref<Vortex::TransformComponent> transformComp;
	Vortex::Ref<Vortex::Framebuffer> m_Framebuffer;

	glm::vec4 color = glm::vec4(1.f);
};