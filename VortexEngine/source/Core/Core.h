#pragma once

#ifdef VE_PLATFORM_WINDOWS
	#ifdef VE_DYNAMIC_LINKING
		#ifdef VE_BUILD_DLL
			#define VORTEX_API __declspec(dllexport)
		#else
			#define VORTEX_API __declspec(dllimport)
		#endif
	#else
		#define VORTEX_API
	#endif

#else 
	#error VortexEngine doesn't support current platform;

#endif

#define VORTEX_BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)