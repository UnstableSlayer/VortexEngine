#include <VortexEngine.h>

class TestGame : public Vortex::App
{
public:
	TestGame();
    ~TestGame();

    virtual void OnStart() override;
	virtual void OnUpdate() override;

	virtual void OnEvent(Vortex::Event &event) override;
    bool OnCameraResize(Vortex::WindowResizeEvent &event);

	public:
		Vortex::Object m_Camera;
};
