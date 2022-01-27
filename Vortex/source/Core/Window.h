#pragma once
#include "Events/Event.h"

namespace Vortex
{
	struct WindowProperties
	{
		std::string title;
		uint32_t width;
		uint32_t height;

		WindowProperties(const std::string& Title = "VortexEngine Example Window",
						 uint32_t Width = 320,
						 uint32_t Height = 240)
			: title(Title), width(Width), height(Height) {}
	};

	class VORTEX_API Window
	{
	public:
		using EventCallback = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;
		virtual const std::string& GetWindowTitle() const = 0;
		virtual const uint32_t GetWindowWidth() const = 0;
		virtual const uint32_t GetWindowHeight() const = 0;

		virtual void SetWindowTitle(const std::string& title) = 0;
		virtual void SetEventCallback(const EventCallback& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void LockCursor(bool enabled) = 0;

		virtual void* GetAPIWindow() const = 0;

		static Ref<Window> Create(const WindowProperties& properties = WindowProperties());
	};
}

