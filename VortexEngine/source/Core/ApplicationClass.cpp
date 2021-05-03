#include <vpch.h>
#include "ApplicationClass.h"

namespace Vortex
{
	ApplicationClass::ApplicationClass()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	ApplicationClass::~ApplicationClass()
	{

	}

	void ApplicationClass::OnStart()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}