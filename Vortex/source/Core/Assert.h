#pragma once
//Temporary
#define VE_ENABLE_ASSERTS

#ifdef VE_ENABLE_ASSERTS
#define VORTEX_ASSERT(x, ...) { if(!(x)) { VORTEX_CORE_ERROR("Assertion Failed: {0} {1} {2}", __VA_ARGS__, __FILE__, __LINE__);} }
#else
#define VORTEX_ASSERT(x, ...)
#endif