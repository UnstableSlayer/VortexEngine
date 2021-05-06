#pragma once
//Temporary
#define VE_ENABLE_ASSERTS

#ifdef VE_ENABLE_ASSERTS
#define VORTEX_CORE_ASSERT(x, ...) { if(!(x)) { VORTEX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define VORTEX_APP_ASSERT(x, ...) { if(!(x)) { VORTEX_APP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define VORTEX_ASSERT(x, ...)
#define VORTEX_CORE_ASSERT(x, ...)
#endif