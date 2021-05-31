#include "vpch.h"
#include "WindowsInput.h"
#include "Core/ApplicationClass.h"

#include <GLFW/glfw3.h>

namespace Vortex
{
    Input* Input::s_Instance = new WindowsInput();

    bool WindowsInput::IsKeyPressedImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(ApplicationClass::Get().GetWindow().GetAPIWindow());

        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }
    bool WindowsInput::IsMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(ApplicationClass::Get().GetWindow().GetAPIWindow());
        auto state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePositionImpl()
    {
        auto window = static_cast<GLFWwindow*>(ApplicationClass::Get().GetWindow().GetAPIWindow());

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return { (float)xpos, (float)ypos };
    }

    float WindowsInput::GetMouseXImpl()
    {
        auto [x, y] = WindowsInput::GetMousePositionImpl();

        return x;
    }

    float WindowsInput::GetMouseYImpl()
    {
        auto [x, y] = WindowsInput::GetMousePositionImpl();

        return y;
    }
}