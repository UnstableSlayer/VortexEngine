#pragma once
#include <string>
#include <fstream>
#include "../Core.h"
#include "../Logger.h"
#include "../Assert.h"

namespace Vortex
{
	class VORTEX_API Shader
	{
	public:
		Shader(const std::string& vertexShaderLoc, const std::string& fragmentShaderLoc)
		{
			std::ifstream ifs(vertexShaderLoc);
			VORTEX_CORE_ASSERT(ifs.is_open(), "VERTEX SHADER FILE NOT FOUND");

			vertexShaderSrc = new std::string();
			while (!ifs.eof())
			{
				std::string line;
				VORTEX_CORE_ASSERT(std::getline(ifs, line), "FAILED READING VERTEX SHADER FILE");
				*vertexShaderSrc += line;
				*vertexShaderSrc += '\n';
			}
			ifs.close();


			ifs.open(fragmentShaderLoc);
			VORTEX_CORE_ASSERT(ifs.is_open(), "VORTEX SHADER FILE NOT FOUND");

			fragmentShaderSrc = new std::string();
			while (!ifs.eof())
			{
				std::string line;
				VORTEX_CORE_ASSERT(std::getline(ifs, line), "FAILED READING FRAGMENT SHADER FILE");
				*fragmentShaderSrc += line;
				*fragmentShaderSrc += '\n';
			}
			ifs.close();
		}
		
		virtual void Compile() = 0;

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetBool(const std::string& name, bool value) = 0;

	public:
		unsigned int ID;

	protected:
		std::string *vertexShaderSrc, *fragmentShaderSrc;
	};
}