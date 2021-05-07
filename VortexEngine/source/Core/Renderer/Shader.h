#pragma once
#include "../Core.h"
#include "../Logger.h"
#include "../Assert.h"

#include <string>
#include <fstream>

namespace Vortex
{
	class VORTEX_API Shader
	{
	public:	
		virtual ~Shader() {}

		virtual void Compile() = 0;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetBool(const std::string& name, bool value) = 0;

		static Shader* Create(const std::string& vertexShaderLoc, const std::string& fragmentShaderLoc);

		void ReadShaderFiles(const std::string& vertexShaderLoc, const std::string& fragmentShaderLoc);

	public:
		unsigned int m_ID;

	protected:
		const char *m_VertexShaderSrc, *m_FragmentShaderSrc;
	};
}