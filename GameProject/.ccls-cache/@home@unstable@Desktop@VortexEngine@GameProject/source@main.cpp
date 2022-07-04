#include "ExampleLayer.h"
#include "EntryPoint.h"
#include "stdio.h"
class GameApplication : public Vortex::ApplicationClass
{
public:
	GameApplication()
	{
		m_Window = Vortex::Window::Create(Vortex::WindowProperties("Vortex Engine Example Window", 640, 360, 320, 180));
		m_Window->SetEventCallback(VORTEX_BIND_EVENT(ApplicationClass::OnEvent));

		//int temp;
	    //scanf("%d", &temp);
		m_Window->SetVSync(false);
		m_Window->LockCursor(true);
		m_Window->SetWindowTitle("Testing Setting");
        VORTEX_APP_INFO("Window done!");
		PushLayer(new ExampleLayer());
	}

	~GameApplication() {}

	virtual void OnUpdate() override
	{
		for (Vortex::Layer* layer : m_LayerStack)
			layer->OnUpdate();

		m_Window->OnUpdate();
	}

	virtual void OnStart() override {}
};

Vortex::ApplicationClass* Vortex::CreateApplication()
{
	return new GameApplication();
}
