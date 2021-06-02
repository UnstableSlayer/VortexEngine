#include "vpch.h"
#include "OpenGLTexture.h"

#include "Core/Logger.h"
#include "Core/Assert.h"
#include "stb_image.h"

#include "glad/glad.h"

namespace Vortex
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		VORTEX_ASSERT(data, "Failed to load image file!");
		m_Width = width;
		m_Height = height;

		GLenum texFormat = 0, dataFormat = 0;
		
		if (channels == 3)
		{
			texFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		else if(channels == 4)
		{
			texFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		m_InternalFormat = texFormat;
		m_DataFormat = dataFormat;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
		glTextureStorage2D(m_ID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_ID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
		
		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(const uint32_t width, const uint32_t height) : m_Width(width), m_Height(height)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
		glTextureStorage2D(m_ID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_ID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_ID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		VORTEX_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(m_ID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}
	unsigned int* OpenGLTexture2D::GetData()
	{
		unsigned int* buffer = nullptr;
		glGetTextureSubImage(m_ID, 0, 0, 0, 0, GetWidth(), GetHeight(), 0, m_DataFormat, GL_UNSIGNED_INT, GetWidth() * GetHeight() * sizeof(unsigned int), buffer);

		return buffer;
	}
}