#include "vpch.h"
#include "Shader.h"

#include "Renderer.h"

#include "Core/Logger.h"
#include "Core/Assert.h"

#include "Platforms/OpenGL/OpenGLShader.h"

namespace Vortex
{
	Shader* Shader::Create(const std::string& vertexShaderLoc, const std::string& fragmentShaderLoc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			VORTEX_ASSERT(false, "No API Selected!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexShaderLoc, fragmentShaderLoc);
		}

		VORTEX_ASSERT(false, "Unknown Renderer API!");
		return nullptr;
	}

	void Shader::ReadShaderFiles(const std::string& vertexShaderLoc, const std::string& fragmentShaderLoc)
	{
		std::string* vShaderSrc = new std::string();
		std::string* fShaderSrc = new std::string();

		std::ifstream ifs(vertexShaderLoc);
		if (!ifs.is_open())
		{
			delete vShaderSrc, fShaderSrc;

			VORTEX_ASSERT(false, "Vertex shader file not found");
			return;
		}

		while (!ifs.eof())
		{
			std::string line;
			if (!std::getline(ifs, line))
			{
				ifs.close();
				delete vShaderSrc, fShaderSrc;

				VORTEX_ASSERT(false, "Failed reading vertex shader file");
				return;
			}

			*vShaderSrc += line;
			*vShaderSrc += '\n';
		}
		ifs.close();


		ifs.open(fragmentShaderLoc);
		if (!ifs.is_open())
		{
			delete vShaderSrc, fShaderSrc;

			VORTEX_ASSERT(false, "Fragment shader file not found");
			return;
		}

		while (!ifs.eof())
		{
			std::string line;
			if (!std::getline(ifs, line))
			{
				ifs.close();
				delete vShaderSrc, fShaderSrc;

				VORTEX_ASSERT(false, "Failed reading fragment shader file");
				return;
			}

			*fShaderSrc += line;
			*fShaderSrc += '\n';
		}
		ifs.close();

		m_VertexShaderSrc = vShaderSrc->c_str();
		m_FragmentShaderSrc = fShaderSrc->c_str();
	}
}