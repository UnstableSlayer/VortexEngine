#pragma once
#include "Core/Layer.h"
#include "Core/Window.h"
#include "Events/MouseEvents.h"
#include "Events/KeyEvent.h"
#include "Events/WindowEvents.h"

namespace Vortex
{
	class VORTEX_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
		bool IsBlockingEvents() { return m_BlockEvents; }

		void SetDarkThemeColors();
	private:
		bool m_BlockEvents = true;
	};
}
