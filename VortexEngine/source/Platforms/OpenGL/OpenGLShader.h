#pragma once
#include "Core/Renderer/Shader.h"

namespace Vortex
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexShaderLoc, const std::string& fragmentShaderLoc);
		virtual ~OpenGLShader();

		virtual void Compile() override;

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix) override;
	};
}