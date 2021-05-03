#pragma once

#ifdef VE_PLATFORM_WINDOWS
	#ifdef VE_BUILD_DLL
		#define VORTEX_API __declspec(dllexport)
	#else
		#define VORTEX_API __declspec(dllimport)
#endif

#else 
	#error VortexEngine Don't support current platform;

#endif

//#ifdef VORTEX_ENABLE_ASSERTS
//	#define VORTEX_ASSERT(x, ...) { if(!(x)) { VORTEX_CORE_ERROR("Assertion failed {0}", __VA_ARGS__); __debugbreak(); } }
//	#define VORTEX_CORE_ASSERT
//#endif
