#include <string>
#include <functional>
#include <sstream>

#include <VortexEngine.h>

class ExampleLayer : public Vortex::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		VORTEX_APP_INFO("ExampleLayer::Update");
	}

	void OnEvent(Vortex::Event& event) override
	{
		VORTEX_APP_TRACE("{0}", event.ToString());
	}
};

class GameApplication : public Vortex::ApplicationClass
{
public :
	GameApplication()
	{
		PushLayer(new ExampleLayer());
	}

	~GameApplication()
	{

	}
};


Vortex::ApplicationClass* Vortex::CreateApplication()
{
	VORTEX_CORE_INFO("Initializating Engine Logger...OK");
	VORTEX_APP_INFO("Initializating Application Logger...OK");

	return new GameApplication();
}

