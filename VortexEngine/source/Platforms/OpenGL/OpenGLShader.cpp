#include "vpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Vortex
{
	OpenGLShader::OpenGLShader(const std::string& vertexShaderLoc, const std::string& fragmentShaderLoc)
	{
		OpenGLShader::ReadShaderFiles(vertexShaderLoc, fragmentShaderLoc);
		OpenGLShader::Compile();
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ID);
	}

	void OpenGLShader::Compile()
	{
		unsigned int vertex, fragment;
		GLint isCompiled;

		// Vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &m_VertexShaderSrc, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint length = 0;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			
			char* infoLog = new char[length];
			glGetShaderInfoLog(vertex, length, &length, infoLog);

			glDeleteShader(vertex);
			delete m_VertexShaderSrc, m_FragmentShaderSrc;

			VORTEX_CORE_ERROR("VERTEX SHADER COMPILATION FAILED: {0}", infoLog);
			VORTEX_NO_CONDITION_ASSERT("");
		}

		// Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &m_FragmentShaderSrc, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint length = 0;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);

			char* infoLog = new char[length];
			glGetShaderInfoLog(fragment, length, &length, infoLog);

			glDeleteShader(vertex);
			glDeleteShader(fragment);
			delete m_VertexShaderSrc, m_FragmentShaderSrc;

			VORTEX_CORE_ERROR("FRAGMENT SHADER COMPILATION FAILED: {0}", infoLog);
			VORTEX_NO_CONDITION_ASSERT("");
		}

		// shader Program
		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertex);
		glAttachShader(m_ID, fragment);
		glLinkProgram(m_ID);

		GLint isLinked = 0;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &isLinked);

		if (isLinked == GL_FALSE)
		{
			GLint length = 0;
			glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &length);

			char* infoLog = new char[length];
			glGetProgramInfoLog(m_ID, length, &length, infoLog);

			glDetachShader(m_ID, vertex);
			glDetachShader(m_ID, fragment);

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			glDeleteProgram(m_ID);
			delete m_VertexShaderSrc, m_FragmentShaderSrc;

			VORTEX_CORE_ERROR("FRAGMENT SHADER COMPILATION FAILED: {0}", infoLog);
			VORTEX_NO_CONDITION_ASSERT("");
		}

		//Detach and Delete
		glDetachShader(m_ID, vertex);
		glDetachShader(m_ID, fragment);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		delete m_VertexShaderSrc, m_FragmentShaderSrc;
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_ID);
	}
	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}
	void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}
}