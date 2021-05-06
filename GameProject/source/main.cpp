#include <string>
#include <functional>
#include <sstream>

#include <VortexEngine.h>
#include <chrono>

class ExampleLayer : public Vortex::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		//VORTEX_APP_INFO("ExampleLayer::Update");
	}

	void OnEvent(Vortex::Event& event) override
	{
		//VORTEX_APP_TRACE("{0}", event.ToString());
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Hello");
		ImGui::Text("Hello World!");
		ImGui::End();
	}
};

class GameApplication : public Vortex::ApplicationClass
{
public :
	GameApplication()
	{
		PushLayer(new ExampleLayer());
		GetWindow().SetVSync(false);
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

