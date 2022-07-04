#include "VortexEditor.h"
#include <EntryPoint.h>

Vortex::ApplicationClass* Vortex::CreateApplication()
{
	VORTEX_CORE_INFO("Initializating Engine Logger...OK");
	VORTEX_APP_INFO("Initializating Application Logger...OK");

	return new VortexEditor();
}