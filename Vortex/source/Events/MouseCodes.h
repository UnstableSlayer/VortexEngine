#pragma once

#define KeyCodeDef(name, code) name = code
#define MOUSEKEYDEFS_H

namespace Vortex
{
	using MouseCode = int8_t;

	namespace MouseKey
	{
		enum : MouseCode
		{
			#include "Input/MouseKeyDefs.h"
		};
	}
}

#undef KeyCodeDef
#undef MOUSEKEYDEFS_H
