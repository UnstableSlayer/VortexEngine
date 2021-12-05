#pragma once

namespace Vortex
{
	class VORTEX_API Input
	{
	public:
		static bool IsKeyPressed(int keycode);
		
		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();
		static std::pair<float, float> GetMouseDelta();
		static float GetMouseX();
		static float GetMouseY();
	};
}