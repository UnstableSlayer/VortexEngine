#include "ApplicationClass.h"
#include <stdio.h>

namespace Vortex
{
	ApplicationClass::ApplicationClass()
	{

	}

	ApplicationClass::~ApplicationClass()
	{

	}

	void ApplicationClass::OnStart()
	{
		while (true) { printf("YES\n"); }
	}
}