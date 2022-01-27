#include "vpch.h"
#include "Shader.h"

#include "Renderer/RendererAPI.h"
#include "Platforms/OpenGL/OpenGLShader.h"

#include <string>
#include <fstream>

namespace Vortex
{
	Ref<Shader> Shader::Create(const std::string& shaderLoc)
	{
		switch (RendererAPI::GetAPI())
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

	void Shader::ReadShadeFile(const std::string& shaderLoc)
	{
		std::string* vShaderSrc = new std::string();
		std::string* fShaderSrc = new std::string();

		std::ifstream ifs(shaderLoc);
		if (!ifs.is_open())
		{
			delete vShaderSrc, fShaderSrc;

			VORTEX_ASSERT(false, "Shader file not found " + shaderLoc);
			return;
		}

		std::string* targetSrc = nullptr;
		while (!ifs.eof())
		{
			std::string line;
			if (!std::getline(ifs, line) && !ifs.eof())
			{
				ifs.close();
                VORTEX_APP_INFO("failed vertex: \n{0}", *vShaderSrc);
                VORTEX_APP_INFO("failed fragment: \n{0}", *fShaderSrc);
				delete vShaderSrc, fShaderSrc;

				VORTEX_ASSERT(false, "Failed reading shader file", shaderLoc);
				return;
			}

			if (!line.compare("#type vertex\r"))
            {
                VORTEX_APP_WARNING("vertex shader init line: {0}", line);
				targetSrc = vShaderSrc;
            }

			else if (!line.compare("#type fragment\r"))
            {
                VORTEX_APP_WARNING("fragment shader init line: {0}", line);
                targetSrc = fShaderSrc;
            }
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
