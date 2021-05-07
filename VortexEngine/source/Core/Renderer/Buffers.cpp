#include "vpch.h"
#include "Buffers.h"

#include "Renderer.h"
#include "Platforms/OpenGL/OpenGLBuffers.h"

namespace Vortex
{
    VertexBuffer* VertexBuffer::Create(float* verticies, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: VORTEX_ASSERT(false, "No API Selected!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(verticies, size);
        }

        VORTEX_ASSERT(false, "Unknown Renderer API!");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: VORTEX_ASSERT(false, "No API Selected!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, count);
        }

        VORTEX_ASSERT(false, "Unknown Renderer API!");
        return nullptr;
    }

    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: VORTEX_ASSERT(false, "No API Selected!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
        }

        VORTEX_ASSERT(false, "Unknown Renderer API!");
        return nullptr;
    }
}
