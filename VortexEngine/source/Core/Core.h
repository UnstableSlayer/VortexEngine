#pragma once

#ifdef VE_PLATFORM_WINDOWS
	#ifdef VE_BUILD_DLL
		#define VORTEX_API __declspec(dllexport)
	#else
		#define VORTEX_API __declspec(dllimport)
#endif

#else 
	#error VortexEngine doesn't support current platform;

#endif

#ifdef VORTEX_ENABLE_ASSERTS
	#define VORTEX_ASSERT(x, ...) { if(!(x)) { VORTEX_CORE_ERROR("Assertion failed {0}", __VA_ARGS__); __debugbreak(); } }
#endif

#define VORTEX_BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)
