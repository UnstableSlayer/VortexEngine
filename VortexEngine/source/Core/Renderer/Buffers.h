#pragma once
#include "../Logger.h"
#include "../Assert.h"

namespace Vortex
{
	/// Buffer Layout ////////////////////////////////////

	enum class ShaderDataType
	{
		None = 0,
		Int, Vec2i, Vec3i, Vec4i,
		Float, Vec2f, Vec3f, Vec4f,
		Mat3, Mat4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Int:			return 4;
		case ShaderDataType::Vec2i:			return 4 * 2;
		case ShaderDataType::Vec3i:			return 4 * 3;
		case ShaderDataType::Vec4i:			return 4 * 4;
		case ShaderDataType::Float:			return 4;
		case ShaderDataType::Vec2f:			return 4 * 2;
		case ShaderDataType::Vec3f:			return 4 * 3;
		case ShaderDataType::Vec4f:			return 4 * 4;
		case ShaderDataType::Mat3:			return 4 * 3 * 3;
		case ShaderDataType::Mat4:			return 4 * 4 * 4;
		case ShaderDataType::Bool:			return 1;
		}

		VORTEX_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Int:			return 1;
			case ShaderDataType::Vec2i:			return 2;
			case ShaderDataType::Vec3i:			return 3;
			case ShaderDataType::Vec4i:			return 4;
			case ShaderDataType::Float:			return 1;
			case ShaderDataType::Vec2f:			return 2;
			case ShaderDataType::Vec3f:			return 3;
			case ShaderDataType::Vec4f:			return 4;
			case ShaderDataType::Mat3:			return 3 * 3;
			case ShaderDataType::Mat4:			return 4 * 4;
			case ShaderDataType::Bool:			return 1;
			}

			VORTEX_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements) 
		{
			CalculateOffsetsAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline const uint32_t& GetStride() const { return m_Stride; }
	
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};


	/// Vertex Buffer ////////////////////////////////////

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() = 0;

		static VertexBuffer* Create(float* verticies, uint32_t size);
	};


	/// Index Buffer ////////////////////////////////////

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};


	/// Vertex Array ////////////////////////////////////
	
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static VertexArray* Create();

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;
	};
}