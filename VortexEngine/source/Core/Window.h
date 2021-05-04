#pragma once
#include "Core.h"
#include "Events/Event.h"

namespace Vortex
{
	struct WindowProperties
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProperties(const std::string& Title = "VortexEngine Example Window",
						 unsigned int Width = 320,
						 unsigned int Height = 240)
			: title(Title), width(Width), height(Height) {}
	};

	class VORTEX_API Window
	{
	public:
		using EventCallback = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;
		virtual unsigned int GetWindowWidth() const = 0;
		virtual unsigned int GetWindowHeight() const = 0;

		virtual void SetEventCallback(const EventCallback& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());
	};
}

