#pragma once
#include <string>
#include <sstream>
#include <functional>
#include <chrono>

#include <VortexEngine.h>

class PlayerLayer : public Vortex::Layer
{
public:
	PlayerLayer();

	void Input();

	virtual void OnUpdate() override;
	virtual void OnEvent(Vortex::Event& event) override;
	virtual void OnImGuiRender() override;

private:
	Vortex::Object m_PlayerObj;
};
