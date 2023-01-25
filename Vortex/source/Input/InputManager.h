#pragma once
#include "Events/Event.h"

namespace Vortex
{
    enum KeyBindingType : int8_t
    {
        #define KEYBINDINGTYPES_H
        #define KeyBindingTypeDef(name, num) name = num
        #include "KeyBindingTypes.h"
        #undef KEYBINDINGTYPES_H
        #undef KeyBindingTypeDef
    };

    static const uint8_t InputCountFromKeyBindingType(KeyBindingType type)
    {
        switch(type)
        {
            case KeyBindingType::Invalid:                return 0; break;
            case KeyBindingType::SingleBool:             return 1; break;
            case KeyBindingType::SingleFloat:            return 1; break;
            case KeyBindingType::OneDimensionalInt:      return 2; break;
            case KeyBindingType::OneDimensionalFloat:    return 2; break;
            case KeyBindingType::TwoDimensionalInt:      return 4; break;
            case KeyBindingType::TwoDimensionalFloat:    return 4; break;
            case KeyBindingType::ThreeDimensionalInt:    return 6; break;
            case KeyBindingType::ThreeDimensionalFloat:  return 6; break;
        }

        return 0;
    }

    enum InputType : int8_t
    {
        Unknown = -1,
        KeyboardInput,
        MouseInput,
        ControllerInput
    };

    struct InputSource
    {
        int32_t keycode;
        InputType inputType;
        uint8_t index;
        uint8_t axis;
    };

    struct KeyBindingData
    {
        InputSource* inputsources;
        KeyBindingType type;
        uint8_t inputCount;
    };

    class VORTEX_API InputManager
    {
    public:
        InputManager();
        ~InputManager() = default;

        void LoadBindings(const char* pathToBindings);
        //virtual void OnEvent(Event& event) = 0;

    private:
        std::unordered_map<const char*, const int32_t> m_KeyCodeEnumStringTable;
        std::unordered_map<const char*, const KeyBindingType> m_BindingTypeStringTable;
        std::unordered_map<const char*, const KeyBindingData> m_KeyBindings;
    };
}
