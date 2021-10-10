#pragma once
#include <glm/glm.hpp>

namespace Vortex
{
	struct FramebufferParams
	{
		uint32_t Width, Height;
		//FramebufferFormat
		uint32_t Samples = 1;

		bool SwapChainTarget = false;

	};

	class VORTEX_API Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual const FramebufferParams& GetParams() const = 0;
		virtual void Invalidate() = 0;
		virtual void Resize(glm::vec2 size) = 0;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual uint32_t GetColorAttachmentID() = 0;
		virtual uint32_t GetDepthAttachmentID() = 0;


		static Ref<Framebuffer> Create(const FramebufferParams& frameBufferParams);
	};
}