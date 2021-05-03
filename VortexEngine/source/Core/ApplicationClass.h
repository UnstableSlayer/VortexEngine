#pragma once
#include "Core.h"
#include "Window.h"

namespace Vortex
{
	class VORTEX_API ApplicationClass
	{
	public:
		ApplicationClass();
		~ApplicationClass();

		void OnStart();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//To be defined in game application
	ApplicationClass* CreateApplication();
}