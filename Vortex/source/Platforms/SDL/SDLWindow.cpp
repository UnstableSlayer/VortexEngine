#include "SDLWindow.h"
#include "vpch.h"

#include "Core/App.h"

#include "Events/KeyEvent.h"
#include "Events/MouseEvents.h"
#include "Events/WindowEvents.h"

#include "SDL_video.h"
#include "SDL_vulkan.h"
#include "backends/imgui_impl_sdl2.h"

namespace Vortex {
static bool b_SDLInitialized = false;

Ref<Window> Window::Create(const WindowProperties &properties) {
  return MakeRef<SDLWindow>(properties);
}

SDLWindow::SDLWindow(const WindowProperties &properties) { Init(properties); }

SDLWindow::~SDLWindow() {}

void SDLWindow::Init(const WindowProperties &properties) {
  m_Data.title = properties.title;
  m_Data.width = properties.width;
  m_Data.height = properties.height;
  m_Data.pixelWidth = properties.pixelWidth;
  m_Data.pixelHeight = properties.pixelHeight;

  VORTEX_ASSERT(properties.pixelWidth != 0,
                "Window pixel width or height can't be 0")

  VORTEX_CORE_TRACE("Creating window '{0}' {1}x{2}", properties.title,
                    properties.width, properties.height);

  if (!b_SDLInitialized) {
    SDL_Init(SDL_INIT_EVERYTHING);
    m_Window = SDL_CreateWindow(m_Data.title.c_str(), SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, (int)m_Data.width,
                                (int)m_Data.height,
                                SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN);
  }

  SDL_AddEventWatch(
      (SDL_EventFilter)[](void *userdata, SDL_Event *event) {
        if (event->type != SDL_WINDOWEVENT ||
            event->window.event != SDL_WINDOWEVENT_RESIZED)
          return 0;

        WindowData &data = *(WindowData *)userdata;
        data.width = event->window.data1;
        data.height = event->window.data2;

        WindowResizeEvent veEvent(event->window.data1, event->window.data2);
        data.eventCallback(veEvent);

        return 0;
      },
      (void *)&m_Data);

  SDL_AddEventWatch(
      (SDL_EventFilter)[](void *userdata, SDL_Event *event) {
        if (event->type != SDL_WINDOWEVENT ||
            event->window.event != SDL_WINDOWEVENT_CLOSE)
          return 0;

        WindowData &data = *(WindowData *)userdata;
        WindowCloseEvent veEvent;
        data.eventCallback(veEvent);

        return 0;
      },
      (void *)&m_Data);

  SDL_AddEventWatch(
      (SDL_EventFilter)[](void *userdata, SDL_Event *event) {
        if (event->type != SDL_KEYDOWN && event->type != SDL_KEYUP)
          return 0;

        WindowData &data = *(WindowData *)userdata;

        auto state = event->key.state;
        uint32_t key = event->key.keysym.scancode;
        switch (state) {
        case SDL_PRESSED: {
          KeyPressedEvent veEvent(key, 0);
          data.eventCallback(veEvent);
          break;
        }
        case SDL_RELEASED: {
          KeyReleasedEvent veEvent(key);
          data.eventCallback(veEvent);
          break;
        }
        default: {
          KeyPressedEvent veEvent(key, 1);
          data.eventCallback(veEvent);
          break;
        }
        }
        return 0;
      },
      (void *)&m_Data);

  SDL_AddEventWatch(
      (SDL_EventFilter)[](void *userdata, SDL_Event *event) {
        if (event->type != SDL_TEXTINPUT)
          return 0;

        WindowData &data = *(WindowData *)userdata;
        KeyTypedEvent veEvent(event->key.keysym.scancode);
        data.eventCallback(veEvent);

        return 0;
      },
      (void *)&m_Data);

  SDL_AddEventWatch(
      (SDL_EventFilter)[](void *userdata, SDL_Event *event) {
        if (event->type != SDL_MOUSEBUTTONDOWN &&
            event->type != SDL_MOUSEBUTTONUP)
          return 0;

        WindowData &data = *(WindowData *)userdata;
        auto state = event->button.state;

        switch (state) {
        case SDL_PRESSED: {
          MouseButtonPressedEvent veEvent(event->button.button);
          data.eventCallback(veEvent);
          break;
        }
        case SDL_RELEASED: {
          MouseButtonReleasedEvent veEvent(event->button.button);
          data.eventCallback(veEvent);
          break;
        }
        }
        return 0;
      },
      (void *)&m_Data);

  SDL_AddEventWatch(
      (SDL_EventFilter)[](void *userdata, SDL_Event *event) {
        if (event->type != SDL_MOUSEWHEEL)
          return 0;

        WindowData &data = *(WindowData *)userdata;
        MouseScrolledEvent veEvent((float)event->wheel.x,
                                   (float)event->wheel.y);
        data.eventCallback(veEvent);

        return 0;
      },
      (void *)&m_Data);

  SDL_AddEventWatch(
      (SDL_EventFilter)[](void *userdata, SDL_Event *event) {
        if (event->type != SDL_MOUSEMOTION)
          return 0;

        WindowData &data = *(WindowData *)userdata;
        MouseMovedEvent veEvent((float)event->motion.x, (float)event->motion.y);
        data.eventCallback(veEvent);
        return 0;
      },
      (void *)&m_Data);
}

void SDLWindow::Close() {
  SDL_DestroyWindow(m_Window);
  SDL_Quit();
}

void SDLWindow::OnUpdate() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
  }
  // if(App::Get().GetImGuiLayer())
  // ImGui_ImplSDL2_ProcessEvent(&event);

  // vkDeviceWaitIdle(device);
}

void SDLWindow::SetVSync(bool enabled) {
  // enabled ? SDL_GL_SetSwapInterval(1) : SDL_GL_SetSwapInterval(0);
  // m_Data.vSync = enabled;
}

bool SDLWindow::IsVSync() const { return m_Data.vSync; }

void SDLWindow::LockCursor(bool enable) {
  // SDL_SetWindowMouseGrab(m_Window, (SDL_bool)enable);
  int result = SDL_SetRelativeMouseMode((SDL_bool)enable);

  VORTEX_ASSERT(result == 0, "SDL couldn't set relative mouse mode: {0}",
                SDL_GetError());
}

int SDLWindow::GetPositionX() const {
  int posX;
  SDL_GetWindowPosition(m_Window, &posX, nullptr);

  return posX;
}

int SDLWindow::GetPositionY() const {
  int posY;
  SDL_GetWindowPosition(m_Window, nullptr, &posY);

  return posY;
}
} // namespace Vortex
