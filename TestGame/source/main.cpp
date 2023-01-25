#include "TestGame.h"
#include "EntryPoint.h"

Vortex::App* Vortex::CreateApplication()
{
	return new TestGame();
}
