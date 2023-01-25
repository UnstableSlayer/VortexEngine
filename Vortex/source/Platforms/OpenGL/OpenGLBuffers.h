#pragma once
#include "Renderer/Buffers.h"

namespace Vortex
{
	class VORTEX_API OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* verticies, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual const BufferLayout& GetLayout() override { return m_Layout; };
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual void SetData(const void* data, uint32_t size) override;

	private:
		unsigned int m_ID;
		BufferLayout m_Layout;
	};

	class VORTEX_API OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual uint32_t GetCount() const override { return m_Count; }
	private:
		unsigned int m_ID;
		uint32_t m_Count;
	};


	class VORTEX_API OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		unsigned int m_ID;

		uint32_t vertexBufferIndexOffset = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};

	class VORTEX_API OpenGLPixelBuffer : public PixelBuffer
	{
	public:
		OpenGLPixelBuffer(uint32_t width, uint32_t height);
		virtual ~OpenGLPixelBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual uint32_t* ReadPixelData(uint32_t textureID) const override;
		virtual void WritePixelData(uint32_t* data, uint32_t size);

	private:
		uint32_t m_ID;
		uint32_t* m_PixelData;

	};
}
