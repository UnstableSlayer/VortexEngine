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

