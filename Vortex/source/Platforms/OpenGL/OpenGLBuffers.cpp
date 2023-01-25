#include "vpch.h"
#include "OpenGLBuffers.h"

#include <glad/gl.h>

namespace Vortex
{
	// Vertex Buffer //////////////////////////////////////////////////////
	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		glCreateBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* verticies, uint32_t size)
	{
		glCreateBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}
	void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}


	// Index buffer //////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count)
	{
		glCreateBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}
	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Int:			return GL_INT;
		case ShaderDataType::UInt:			return GL_UNSIGNED_INT;
		case ShaderDataType::Vec2i:			return GL_INT;
		case ShaderDataType::Vec3i:			return GL_INT;
		case ShaderDataType::Vec4i:			return GL_INT;
		case ShaderDataType::Float:			return GL_FLOAT;
		case ShaderDataType::Vec2f:			return GL_FLOAT;
		case ShaderDataType::Vec3f:			return GL_FLOAT;
		case ShaderDataType::Vec4f:			return GL_FLOAT;
		case ShaderDataType::Mat3:			return GL_FLOAT;
		case ShaderDataType::Mat4:			return GL_FLOAT;
		case ShaderDataType::Bool:			return GL_BOOL;
		}

		return GL_INVALID_ENUM;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_ID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_ID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_ID);
	}
	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_ID);
		vertexBuffer->Bind();

		uint32_t index = vertexBufferIndexOffset;
		auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(const void*)element.Offset);

			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);

		vertexBufferIndexOffset = index;
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_ID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;

		glBindVertexArray(0);
	}

	OpenGLPixelBuffer::OpenGLPixelBuffer(uint32_t width, uint32_t height)
	{
		glCreateBuffers(1, &m_ID);
		glBindBuffer(GL_PIXEL_PACK_BUFFER, m_ID);
		//glBufferData(GL_PIXEL_PACK_BUFFER, width * height * sizeof(uint32_t), m_PixelData, GL_STREAM_READ);
	}

	OpenGLPixelBuffer::~OpenGLPixelBuffer()
	{
		glDeleteBuffers(1, &m_ID);
		delete m_PixelData;
	}

	void OpenGLPixelBuffer::Bind() const
	{
		glBindBuffer(GL_PIXEL_PACK_BUFFER, m_ID);
	}

	void OpenGLPixelBuffer::UnBind() const
	{
		glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
	}

	uint32_t* OpenGLPixelBuffer::ReadPixelData(uint32_t textureID) const
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_RGBA16, 0);
		uint32_t* data = (uint32_t*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);

		//VORTEX_ASSERT(data != nullptr, "glMapBuffer failed!");
		if(data == nullptr)
			VORTEX_CORE_ERROR("WHY");

		for (int i = 0; i < 10; i++) {
			VORTEX_CORE_INFO("Data {0}: {1}", i, *(data + i));
		}

		return data;
	}

	void OpenGLPixelBuffer::WritePixelData(uint32_t *data, uint32_t size)
	{

	}
}
