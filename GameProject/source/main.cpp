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
	return new GameApplication();
}

