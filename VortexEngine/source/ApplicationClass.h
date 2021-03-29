#pragma once
#include "Core.h"

namespace Vortex
{
	class VORTEX_API ApplicationClass
	{
	public:
		ApplicationClass();
		~ApplicationClass();

		void OnStart();
	};

	//To be defined in game application
	ApplicationClass* CreateApplication();
}