#include "vpch.h"
#include "Framebuffer.h"

#include "Renderer/RendererAPI.h"
#include "Platforms/OpenGL/OpenGLFramebuffer.h"

namespace Vortex
{
    Ref<Framebuffer> Framebuffer::Create(const FramebufferParams& frameBufferParams)
    {
        switch (RendererAPI::GetAPI())
        {
        case RendererAPI::API::None: VORTEX_ASSERT(false, "No API Selected!"); return nullptr;
        case RendererAPI::API::OpenGL: return MakeRef<OpenGLFramebuffer>(frameBufferParams);
        }

        VORTEX_ASSERT(false, "Unknown Renderer API!");
        return nullptr;
    }
}