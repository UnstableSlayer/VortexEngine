#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

//#include "Core/Allocator.h"

//#define malloc(x) Vortex::Allocator::vmalloc(x)
//#define free(x) Vortex::Allocator::vfree(x)

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <coroutine>
#include <thread>
#include <mutex>

#ifdef VE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif


//#define malloc(x) Vortex::Allocator::vmalloc(x)
//#define free(x) Vortex::Allocator::vfree(x)

#include "Core/Core.h"
#include "Core/RefCounter.h"
#include "Core/Assert.h"
#include "Core/Logger.h"
#include "Core/Time.h"
