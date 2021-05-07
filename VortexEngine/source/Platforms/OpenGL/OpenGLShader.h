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

		virtual void SetInt(const std::string& name, int value) override {};
		virtual void SetFloat(const std::string& name, float value) override {};
		virtual void SetBool(const std::string& name, bool value) override {};
	};
}