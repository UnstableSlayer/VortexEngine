#include "vpch.h"
#include "Texture.h"

#include "Renderer/RendererAPI.h"
#include "Platforms/OpenGL/OpenGLTexture.h"

namespace Vortex
{
    Ref<Texture2D> Texture2D::Create(const uint32_t id)
    {
        switch (RendererAPI::GetAPI())
        {
        case RendererAPI::API::None: VORTEX_ASSERT(false, "No API Selected!"); return nullptr;
        case RendererAPI::API::OpenGL: return MakeRef<OpenGLTexture2D>(id);
        }

        VORTEX_ASSERT(false, "Unknown Renderer API!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(const uint32_t width, const uint32_t height)
    {
        switch (RendererAPI::GetAPI())
        {
        case RendererAPI::API::None: VORTEX_ASSERT(false, "No API Selected!"); return nullptr;
        case RendererAPI::API::OpenGL: return MakeRef<OpenGLTexture2D>(width, height);
        }

        VORTEX_ASSERT(false, "Unknown Renderer API!");
        return nullptr;
    }


    Ref<Texture2D> Texture2D::Create(const std::string& path, TextureFormat format, TextureWrap wrap, TextureFilter filter)
    {
        switch (RendererAPI::GetAPI())
        {
        case RendererAPI::API::None: VORTEX_ASSERT(false, "No API Selected!"); return nullptr;
        case RendererAPI::API::OpenGL: return MakeRef<OpenGLTexture2D>(path, format, wrap, filter);
        }

        VORTEX_ASSERT(false, "Unknown Renderer API!");
        return nullptr;
    }
}
