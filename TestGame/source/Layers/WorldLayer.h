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

private:
    Vortex::Object m_FractalQuad;

    Vortex::JobData<uint32_t*> m_MandelbrotJobs[8];
    uint32_t* m_CombinedMandelbrotTex;

    Vortex::Object ship;
    Vortex::Ref<Vortex::Framebuffer> m_Framebuffer;
};
