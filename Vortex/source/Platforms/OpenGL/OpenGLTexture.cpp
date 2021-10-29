#include "vpch.h"
#include "OpenGLTexture.h"
#include "OpenGLTextureEnums.h"

#include <stb_image.h>
#include <glad/gl.h>

namespace Vortex
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path, TextureFormat format, TextureWrap wrap, TextureFilter filter)
		: m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		VORTEX_ASSERT(data, "Failed to load image file: ", path);
		m_Width = width;
		m_Height = height;

		#pragma region TextureFormat
		auto& [texFormat, dataFormat] = TextureFormatToAPIEnum(format);

		if (channels != 3 && dataFormat == GL_RGB || channels != 4 && dataFormat == GL_RGBA)
			VORTEX_CORE_WARNING("Texture channel count doesn't match texture format. Possible visual artifacts: {0}", path);

		m_InternalFormat = texFormat;
		m_DataFormat = dataFormat;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
		glTextureStorage2D(m_ID, 1, m_InternalFormat, m_Width, m_Height);
#pragma endregion

		#pragma region TextureFilter
		GLenum texFilter = TextureFilterToAPIEnum(filter);

		glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, texFilter);
		glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, texFilter);
#pragma endregion

		#pragma region TextureWrap
		GLenum texWrap = TextureWrapToApiEnum(wrap);

		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, texWrap);
		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, texWrap);
#pragma endregion

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

	void OpenGLTexture2D::MakeHandleResident() const
	{
		uint64_t handle = glGetTextureHandleARB(m_ID);
		glMakeTextureHandleResidentARB(handle);
	}

	void OpenGLTexture2D::MakeHandleNonResident() const
	{
		uint64_t handle = glGetTextureHandleARB(m_ID);
		glMakeTextureHandleNonResidentARB(handle);
	}

	uint64_t OpenGLTexture2D::GetBindlessHandle() const
	{
		return glGetTextureHandleARB(m_ID);
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
		glGetTextureSubImage(m_ID, 0, 0, 0, 0, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_INT, m_Width * m_Height * sizeof(unsigned int), buffer);

		return buffer;
	}
}