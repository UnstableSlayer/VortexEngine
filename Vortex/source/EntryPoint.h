#pragma once
//#define malloc(x) Vortex::Allocator::vmalloc(x)
//#define free(x) Vortex::Allocator::vfree(x)
//#ifdef VE_PLATFORM_WINDOWS

extern Vortex::App* Vortex::CreateApplication();

int main(int argc, char** argv)
{
	//Vortex::Allocator::InitializeAllocator(2 * 1024 * 1024 * 1024);
	Vortex::Logger::Init();
	auto app = Vortex::CreateApplication();
	app->OnCreate();
	delete app;
}

//#endif
