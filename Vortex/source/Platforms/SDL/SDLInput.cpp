#include "vpch.h"
#include "Input/Input.h"
#include "Core/App.h"
#include "Events/WindowEvents.h"

#include <SDL2/SDL.h>

namespace Vortex
{
    bool Input::IsKeyPressed(int keycode)
    {
        const uint8_t* sdlKeyStateArray = SDL_GetKeyboardState(NULL);
        auto state = sdlKeyStateArray[SDL_GetScancodeFromKey(keycode)];
        return state;
    }
    bool Input::IsControllerButtonPressed(int keycode, int controllerIndex)
    {
        auto a = SDL_GameControllerOpen(controllerIndex);
        const bool state = SDL_GameControllerGetButton(a, (SDL_GameControllerButton)keycode);
        return state;
    }

    bool Input::IsMouseButtonPressed(int button)
    {
        const uint32_t mouseStateArray = SDL_GetMouseState(NULL, NULL);
        auto state = (mouseStateArray & SDL_BUTTON(button));

        return state;
    }

    std::pair<float, float> Input::GetMouseDelta()
    {
        int xPos, yPos;
        SDL_GetRelativeMouseState(&xPos, &yPos);

        return { (float)xPos, (float)yPos };
    }
    std::pair<float, float> Input::GetMousePosition()
    {
        auto window = static_cast<SDL_Window*>(App::Get().GetWindow().GetAPIWindow());

        int xPos, yPos;
        SDL_GetGlobalMouseState(&xPos, &yPos);

        int xWinPos, yWinPos;
        SDL_GetWindowPosition(window, &xWinPos, &yWinPos);

        return { (float)(xPos - xWinPos), (float)(yPos - yWinPos) };
    }

    float Input::GetMouseX()
    {
        auto [x, y] = Input::GetMousePosition();

        return x;
    }
    float Input::GetMouseY()
    {
        auto [x, y] = Input::GetMousePosition();

        return y;
    }
}
