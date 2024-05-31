#pragma once
#include <string>
#include <sstream>
#include <functional>
#include <chrono>

#include <VortexEngine.h>

class RenderLayer : public Vortex::Layer
{
public:
	RenderLayer();

	void Input();

	virtual void OnUpdate() override;
	//virtual void OnEvent(Vortex::Event& event) override;
};
