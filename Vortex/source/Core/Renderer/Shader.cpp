#include "vpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platforms/OpenGL/OpenGLShader.h"

#include <string>
#include <fstream>

namespace Vortex
{
	Ref<Shader> Shader::Create(const std::string& shaderLoc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			VORTEX_ASSERT(false, "No API Selected!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return MakeRef<OpenGLShader>(shaderLoc);
		}

		VORTEX_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	void Shader::ReadShaderFiles(const std::string& shaderLoc)
	{
		std::string* vShaderSrc = new std::string();
		std::string* fShaderSrc = new std::string();

		std::ifstream ifs(shaderLoc);
		if (!ifs.is_open())
		{
			delete vShaderSrc, fShaderSrc;

			VORTEX_ASSERT(false, "Shader file not found");
			return;
		}

		std::string* targetSrc;
		while (!ifs.eof())
		{
			std::string line;
			if (!std::getline(ifs, line))
			{
				ifs.close();
				delete vShaderSrc, fShaderSrc;

				VORTEX_ASSERT(false, "Failed reading shader file");
				return;
			}

			if (line == "#type vertex")
				targetSrc = vShaderSrc;

			else if (line == "#type fragment")
				targetSrc = fShaderSrc;

			else
			{
				*targetSrc += line;
				*targetSrc += '\n';
			}
		}
		ifs.close();

		m_VertexShaderSrc = vShaderSrc->c_str();
		m_FragmentShaderSrc = fShaderSrc->c_str();
	}
}