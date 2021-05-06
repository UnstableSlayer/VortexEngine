#include "vpch.h"
#include "OpenGLShader.h"
#include <glad/glad.h>

namespace Vortex
{
	OpenGLShader::OpenGLShader(const std::string& vertexShaderLoc, const std::string& fragmentShaderLoc) : Shader(vertexShaderLoc, fragmentShaderLoc)
	{
		VORTEX_CORE_TRACE("VERTEX: {0} \n FRAGMENT: {1}", vertexShaderSrc->c_str(), fragmentShaderSrc->c_str());
		OpenGLShader::Compile();
	}

	void OpenGLShader::Compile()
	{
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		const char* vShaderSrc = vertexShaderSrc->c_str();
		const char* fShaderSrc = fragmentShaderSrc->c_str();

		// Vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderSrc, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		VORTEX_CORE_ASSERT(success, "VERTEX SHADER COMPILATION FAILED");
		//glGetShaderInfoLog(vertex, 512, NULL, infoLog);

		// Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderSrc, NULL);
		glCompileShader(fragment);

		// shader Program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		VORTEX_CORE_ASSERT(success, "FRAGMENT SHADER COMPILATION FAILED");

		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		delete vertexShaderSrc, fragmentShaderSrc;
	}
}