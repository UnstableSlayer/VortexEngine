#include "vpch.h"
#include "InputManager.h"

#include <fstream>

#define KEYDEFS_H
#define CONTROLLERKEYDEFS_H
#define MOUSEKEYDEFS_H

#define KEYBINDINGTYPES_H

namespace Vortex
{
    InputManager::InputManager()
    {
        m_KeyCodeEnumStringTable = {
            #define KeyCodeDef(name, code) {"Keyboard::"#name, code}
            #include "KeyDefs.h"
            #undef KeyCodeDef

            #define KeyCodeDef(name, code) {"Controller::"#name, code}
            #include "ControllerKeyDefs.h"
            #undef KeyCodeDef

            #define KeyCodeDef(name, code) {"Mouse::"#name, code}
            #include "MouseKeyDefs.h"
            #undef KeyCodeDef
        };

        m_BindingTypeStringTable = {
            #define KeyBindingTypeDef(name, num) {#name, num}
            #include "KeyBindingTypes.h"
            #undef KeyBindingTypeDef
        };

        VORTEX_APP_INFO("KeyCodeEnumStringTable:");
        for(const auto & [key, value] : m_KeyCodeEnumStringTable)
            VORTEX_APP_INFO("        {0}:{1}", key, value);
    }

    void InputManager::LoadBindings(const char* pathToBindings)
    {
        std::ifstream ifs(pathToBindings);

        if(!ifs.is_open())
        {
            VORTEX_ASSERT(false, "Key bindings file not found: {0}", pathToBindings);
            return;
        }


        std::string name;
        KeyBindingData data;

        unsigned int currentValue = 0;
        unsigned int currentLine = 0;

        std::string currentValueStr = "value0";

        while(!ifs.eof())
        {

            std::string line;
            if(!std::getline(ifs, line) && !ifs.eof())
            {
                VORTEX_ASSERT(false, "Failed to read key bindings file: {0}", pathToBindings);
                return;
            }

            currentLine++;

            if(!line.compare("BeginBinding(\""))
            {
                if(!line.ends_with("\")"))
                {
                    VORTEX_ASSERT(false, "Key bindings file expected ')': {0}:{1}", pathToBindings, currentLine);
                    return;
                }

                unsigned int nameIndexStart = line.find("BeginBinding(\"");
                unsigned int nameLength = line.find("\")") - nameIndexStart;
                name = line.substr(nameIndexStart, nameLength);
            }

            if(!line.compare("type "))
            {
                unsigned int typeIndexStart = line.find("type ");
                uint8_t bindingType = m_BindingTypeStringTable[line.substr(typeIndexStart).c_str()];

                data.inputCount = InputCountFromKeyBindingType((KeyBindingType)bindingType);

            }

            if(!line.compare(currentValueStr))
            {
                unsigned int valueIndexStart = line.find(currentValueStr);
                if(!line.compare("&&"))
                {

                }
            }

        }
    }
}

#undef KEYDEFS_H
#undef CONTROLLERKEYDEFS_H
#undef MOUSEKEYDEFS_H

#undef KEYBINDINGTYPES_H
