#pragma once
#include "Core/Renderer/Framebuffer.h"

namespace Vortex
{
	class VORTEX_API OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferParams& params);
		virtual ~OpenGLFramebuffer();

		virtual void Invalidate() override;
		virtual void Resize(glm::vec2 size) override;

		virtual void Bind() override;
		virtual void UnBind() override;

		virtual uint32_t GetColorAttachmentID() override { return m_ColorAttachment; }
		virtual uint32_t GetDepthAttachmentID() override { return m_DepthAttachment; }

		virtual const FramebufferParams& GetParams() const override { return m_Params; }

	private:
		uint32_t m_ID;
		uint32_t m_ColorAttachment;
		uint32_t m_DepthAttachment;
		FramebufferParams m_Params;
	};
}