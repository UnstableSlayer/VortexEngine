#pragma once

namespace Vortex
{
	class VORTEX_API GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		virtual void Destroy() = 0;
	};
}