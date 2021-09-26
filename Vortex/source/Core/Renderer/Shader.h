#pragma once
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
		virtual ~Shader() = default;

		virtual void Compile() = 0;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static Ref<Shader> Create(const std::string& shaderLoc);

		virtual void SetUniformInt(const std::string& name, int value) = 0;
		virtual void SetUniformIntArray(const std::string& name, int* value, uint32_t count) = 0;
		virtual void SetUniformVec1(const std::string& name, float value) = 0;
		virtual void SetUniformVec2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetUniformVec3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetUniformVec4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetUniformMat3(const std::string& name, const glm::mat3& value) = 0;
		virtual void SetUniformMat4(const std::string& name, const glm::mat4& value) = 0;

	protected:
		void ReadShadeFile(const std::string& shaderLoc);

	public:
		uint32_t m_ID;

	protected:
		const char *m_VertexShaderSrc, *m_FragmentShaderSrc;
	};
}