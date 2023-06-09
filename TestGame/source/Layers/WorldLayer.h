#pragma once
#include <string>
#include <sstream>
#include <functional>
#include <chrono>

#include <VortexEngine.h>

class WorldLayer : public Vortex::Layer
{
public:
	WorldLayer();

	void Input();

	virtual void OnUpdate() override;
	//virtual void OnEvent(Vortex::Event& event) override;
	virtual void OnImGuiRender() override;
};
