#include "vpch.h"
#include "Buffers.h"

#include "RendererAPI.h"
#include "Platforms/OpenGL/OpenGLBuffers.h"

namespace Vortex
{
    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        switch (RendererAPI::GetAPI())
        {
        case RendererAPI::API::None: VORTEX_ASSERT(false, "No API Selected!"); return nullptr;
        case RendererAPI::API::OpenGL: return MakeRef<OpenGLVertexBuffer>(size);
        }

        VORTEX_ASSERT(false, "Unknown Renderer API!");
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(float* verticies, uint32_t size)
    {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None: VORTEX_ASSERT(false, "No API Selected!"); return nullptr;
            case RendererAPI::API::OpenGL: return MakeRef<OpenGLVertexBuffer>(verticies, size);
        }

        VORTEX_ASSERT(false, "Unknown Renderer API!");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None: VORTEX_ASSERT(false, "No API Selected!"); return nullptr;
            case RendererAPI::API::OpenGL: return MakeRef<OpenGLIndexBuffer>(indices, count);
        }

        VORTEX_ASSERT(false, "Unknown Renderer API!");
        return nullptr;
    }

    Ref<VertexArray> VertexArray::Create()
    {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::None: VORTEX_ASSERT(false, "No API Selected!"); return nullptr;
            case RendererAPI::API::OpenGL: return MakeRef<OpenGLVertexArray>();
        }

        VORTEX_ASSERT(false, "Unknown Renderer API!");
        return nullptr;
    }
}
