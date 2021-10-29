#pragma once
#include "Core\Renderer\Texture.h"
#include <glm/glm.hpp>

namespace Vortex
{
	class VORTEX_API OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path, TextureFormat format, TextureWrap wrap, TextureFilter filter);
		OpenGLTexture2D(const uint32_t width, const uint32_t height);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetID() const override { return m_ID; }
		virtual uint64_t GetBindlessHandle() const override;
		virtual const char* GetPath() const override { return m_Path.c_str(); }

		virtual glm::vec2 GetSize() const override { return { m_Width, m_Height }; }

		virtual void Bind(uint32_t slot = 0) const override;
		virtual void MakeHandleResident() const override;
		virtual void MakeHandleNonResident() const override;
		virtual void SetData(void* data, uint32_t size) override;
		virtual unsigned int* GetData() override;

	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_ID;

		unsigned int m_InternalFormat, m_DataFormat;
	};
}