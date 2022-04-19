#pragma once
#include "Renderer/Shader.h"

namespace Vortex
{
	typedef int GLint;

	class VORTEX_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& shaderLoc);
		virtual ~OpenGLShader();

		virtual void Compile() override;

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetUniformInt(const std::string& name, int value) override;
		virtual void SetUniformIntArray(const std::string& name, int* value, uint32_t count) override;
		virtual void SetUniformVec1(const std::string& name, float value) override;
		virtual void SetUniformVec2(const std::string& name, const glm::vec2& value) override;
		virtual void SetUniformVec3(const std::string& name, const glm::vec3& value) override;
		virtual void SetUniformVec4(const std::string& name, const glm::vec4& value) override;
		virtual void SetUniformMat3(const std::string& name, const glm::mat3& value) override;
		virtual void SetUniformMat4(const std::string& name, const glm::mat4& value) override;
		virtual void SetUniformTexHandle(const std::string& name, uint64_t value) override;

	private:
		GLint GetUniformLocation(const std::string& name) const;

	private:
		mutable std::unordered_map<std::string, GLint> m_CachedUniformLocations;
	};
}
