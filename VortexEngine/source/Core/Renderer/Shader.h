#pragma once
#include "../Core.h"
#include "../Logger.h"
#include "../Assert.h"

#include <glm/glm.hpp>

namespace Vortex
{
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

	class VORTEX_API Shader
	{
	public:	
		virtual ~Shader() {}

		virtual void Compile() = 0;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static Shader* Create(const std::string& vertexShaderLoc, const std::string& fragmentShaderLoc);

		void ReadShaderFiles(const std::string& vertexShaderLoc, const std::string& fragmentShaderLoc);

		virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
	public:
		unsigned int m_ID;

	protected:
		const char *m_VertexShaderSrc, *m_FragmentShaderSrc;
	};
}