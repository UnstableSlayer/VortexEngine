#pragma once
#include <string>
#include <sstream>
#include <functional>
#include <chrono>

#include <VortexEngine.h>

#include "CustomScene.h"

class EditorLayer : public Vortex::Layer
{
public:
	EditorLayer();

	void Input();

	virtual void OnUpdate() override;
	virtual void OnImGuiRender() override;

	virtual void OnEvent(Vortex::Event& event) override;
	bool OnCameraResize(Vortex::WindowResizeEvent& event);

private:
	CustomScene m_Scene;
	Vortex::Object m_Camera;

	Vortex::Ref<Vortex::Framebuffer> m_ViewportFB;
};
