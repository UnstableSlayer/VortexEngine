#include "vpch.h"
#include "Buffers.h"

#include "Renderer.h"
#include "Platforms/OpenGL/OpenGLBuffers.h"

namespace Vortex
{
    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None: VORTEX_ASSERT(false, "No API Selected!"); return nullptr;
        case RendererAPI::API::OpenGL: return Ref<OpenGLVertexBuffer>(new OpenGLVertexBuffer(size));
        }

        VORTEX_ASSERT(false, "Unknown Renderer API!");
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(float* verticies, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: VORTEX_ASSERT(false, "No API Selected!"); return nullptr;
            case RendererAPI::API::OpenGL: return Ref<OpenGLVertexBuffer>(new OpenGLVertexBuffer(verticies, size));
        }

        VORTEX_ASSERT(false, "Unknown Renderer API!");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: VORTEX_ASSERT(false, "No API Selected!"); return nullptr;
            case RendererAPI::API::OpenGL: return Ref<OpenGLIndexBuffer>(new OpenGLIndexBuffer(indices, count));
        }

        VORTEX_ASSERT(false, "Unknown Renderer API!");
        return nullptr;
    }

    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: VORTEX_ASSERT(false, "No API Selected!"); return nullptr;
            case RendererAPI::API::OpenGL: return Ref<OpenGLVertexArray>(new OpenGLVertexArray());
        }

        VORTEX_ASSERT(false, "Unknown Renderer API!");
        return nullptr;
    }
}
