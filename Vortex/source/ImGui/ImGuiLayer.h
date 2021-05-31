#pragma once
#include "../Core/Core.h"
#include "../Core/Layer.h"
#include "../Core/Window.h"
#include "../Core/Events/MouseEvents.h"
#include "../Core/Events/KeyEvent.h"
#include "../Core/Events/WindowEvents.h"

namespace Vortex
{
	class VORTEX_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.f;
	};
}
