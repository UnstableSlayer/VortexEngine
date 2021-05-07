#pragma once
//Temporary
#define VE_ENABLE_ASSERTS

#ifdef VE_ENABLE_ASSERTS
#define VORTEX_ASSERT(x, ...) { if(!(x)) { VORTEX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define VORTEX_NO_CONDITION_ASSERT(...) { VORTEX_APP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }
#else
#define VORTEX_ASSERT(x, ...)
#define VORTEX_NO_CONDITION_ASSERT(x, ...)
#endif