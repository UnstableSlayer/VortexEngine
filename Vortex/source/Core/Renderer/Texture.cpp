#include "vpch.h"
#include "Texture.h"

#include "RendererAPI.h"
#include "Platforms/OpenGL/OpenGLTexture.h"

namespace Vortex
{
    Ref<Texture2D> Texture2D::Create(const uint32_t width, const uint32_t height)
    {
        switch (RendererAPI::GetAPI())
        {
        case RendererAPI::API::None: VORTEX_ASSERT(false, "No API Selected!"); return nullptr;
        case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture>(width, height);
        }

        VORTEX_ASSERT(false, "Unknown Renderer API!");
        return nullptr;
    }


    Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
        switch (RendererAPI::GetAPI())
        {
        case RendererAPI::API::None: VORTEX_ASSERT(false, "No API Selected!"); return nullptr;
        case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture>(path);
        }

        VORTEX_ASSERT(false, "Unknown Renderer API!");
        return nullptr;
	}
}