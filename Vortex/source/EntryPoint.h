#pragma once

#ifdef VE_PLATFORM_WINDOWS

extern Vortex::ApplicationClass* Vortex::CreateApplication();

int main(int argc, char** argv)
{
	Vortex::Logger::Init();
	auto app = Vortex::CreateApplication();
	app->OnCreate();
	delete app;
}

#endif