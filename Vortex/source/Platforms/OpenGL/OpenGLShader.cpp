#include "vpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Vortex
{
	OpenGLShader::OpenGLShader(const std::string& shaderLoc)
	{
		OpenGLShader::ReadShadeFile(shaderLoc);
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

			VORTEX_ASSERT(false, "VERTEX SHADER COMPILATION FAILED: ", infoLog);
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

			VORTEX_ASSERT(false, "FRAGMENT SHADER COMPILATION FAILED: ", infoLog);
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

			VORTEX_ASSERT(false, "SHADER PROGRAM FAILED: ", infoLog);
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

	void OpenGLShader::SetUniformInt(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}
	void OpenGLShader::SetUniformIntArray(const std::string& name, int* value, uint32_t count)
	{
		glUniform1iv(GetUniformLocation(name), count, value);
	}
	void OpenGLShader::SetUniformVec1(const std::string& name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}
	void OpenGLShader::SetUniformVec2(const std::string& name, const glm::vec2& value)
	{
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}
	void OpenGLShader::SetUniformVec3(const std::string& name, const glm::vec3& value)
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}
	void OpenGLShader::SetUniformVec4(const std::string& name, const glm::vec4& value)
	{
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}
	void OpenGLShader::SetUniformMat3(const std::string& name, const glm::mat3& value)
	{
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}
	void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& value)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	GLint OpenGLShader::GetUniformLocation(const std::string& name) const
	{
		if (m_CachedUniformLocations.find(name) != m_CachedUniformLocations.end())
			return m_CachedUniformLocations[name];

		m_CachedUniformLocations[name] = glGetUniformLocation(m_ID, name.c_str());
		return m_CachedUniformLocations[name];
	}
}