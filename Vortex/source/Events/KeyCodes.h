#pragma once

#define KeyCodeDef(name, code) name = code
#define KEYDEFS_H
#define CONTROLLERKEYDEFS_H

namespace Vortex
{
	using KeyCode = int32_t;

    namespace Key
    {
    enum : KeyCode
	{
        #include "Input/KeyDefs.h"
	};
    }

    namespace Controller
    {
    enum : KeyCode
    {
        #include "Input/ControllerKeyDefs.h"
    };
    }
}

#undef KeyCodeDef
#undef KEYDEFS_H
#undef CONTROLLERKEYDEFS_H
