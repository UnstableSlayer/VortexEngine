#pragma once
#include "Core/Renderer/Texture.h"
#include <glad/glad.h>

namespace Vortex
{
	static std::pair<GLenum, GLenum> TextureFormatToAPIEnum(TextureFormat format)
	{
		GLenum texFormat, dataFormat = GL_NONE;
		switch (format)
		{
		case TextureFormat::AUTO: texFormat = GL_RGBA8; dataFormat = GL_RGBA; break;

		case TextureFormat::RGB4: texFormat = GL_RGB4; dataFormat = GL_RGB; break;
		case TextureFormat::RGB8: texFormat = GL_RGB8; dataFormat = GL_RGB; break;
		case TextureFormat::RGB16: texFormat = GL_RGB16; dataFormat = GL_RGB; break;
		case TextureFormat::RGB16F: texFormat = GL_RGB16F; dataFormat = GL_RGB; break;
		case TextureFormat::RGB32F: texFormat = GL_RGB32F; dataFormat = GL_RGB; break;
		case TextureFormat::RGBA4: texFormat = GL_RGBA4; dataFormat = GL_RGBA; break;
		case TextureFormat::RGBA8: texFormat = GL_RGBA8; dataFormat = GL_RGBA; break;
		case TextureFormat::RGBA16: texFormat = GL_RGBA16; dataFormat = GL_RGBA; break;
		case TextureFormat::RGBA16F: texFormat = GL_RGBA16F; dataFormat = GL_RGBA; break;
		case TextureFormat::RGBA32F: texFormat = GL_RGBA32F; dataFormat = GL_RGBA; break;

		case TextureFormat::DEPTH: texFormat = GL_DEPTH24_STENCIL8; break;
		case TextureFormat::DEPTH24STENCIL8: texFormat = GL_DEPTH24_STENCIL8; break;
		case TextureFormat::DEPTH32FSTENCIL8: texFormat = GL_DEPTH32F_STENCIL8; break;

		default: VORTEX_ASSERT(false, "Invalid TextureFormat!");
		}

		return std::pair<GLenum, GLenum>(texFormat, dataFormat);
	}
	static GLenum TextureFilterToAPIEnum(TextureFilter filter)
	{
		GLenum texFilter;
		switch (filter)
		{
		case TextureFilter::NEAREST: texFilter = GL_NEAREST; break;
		case TextureFilter::LINEAR: texFilter = GL_LINEAR; break;

		default: VORTEX_ASSERT(false, "Invalid TextureFilter!");
		}

		return texFilter;
	}
	static GLenum TextureWrapToApiEnum(TextureWrap wrap)
	{
		uint32_t texWrap;
		switch (wrap)
		{
		case TextureWrap::REPEAT: texWrap = GL_REPEAT; break;
		case TextureWrap::MIRRORED_REPEAT: texWrap = GL_MIRRORED_REPEAT; break;
		case TextureWrap::CLAMP_TO_EDGE: texWrap = GL_CLAMP_TO_EDGE; break;
		case TextureWrap::CLAMP_TO_BORDER: texWrap = GL_CLAMP_TO_BORDER; break;

		default: VORTEX_ASSERT(false, "Invalid TextureWrap!");
		}
		return texWrap;
	}

	static bool IsDepthTexture(TextureFormat format)
	{
		switch (format)
		{
		case TextureFormat::DEPTH: return true;
		case TextureFormat::DEPTH24STENCIL8: return true;
		case TextureFormat::DEPTH32FSTENCIL8: return true;
		}

		return false;
	}
}