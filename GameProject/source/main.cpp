#include <VortexEngine.h>

class GameApplication : public Vortex::ApplicationClass
{
public :
	GameApplication()
	{

	}

	~GameApplication()
	{

	}
};


Vortex::ApplicationClass* Vortex::CreateApplication()
{
	VORTEX_CORE_INFO("Initializating Engine Logger...Success");
	VORTEX_APP_INFO("Initializating Application Logger...Success");

	return new GameApplication();
}

