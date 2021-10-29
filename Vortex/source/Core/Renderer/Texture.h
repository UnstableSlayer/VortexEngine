#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Vortex
{
	enum class TextureFormat
	{
		NONE = -1,

		AUTO,

		//Color
		RGB4,
		RGB8,
		RGB16,
		RGB16F,
		RGB32F,
		RGBA4,
		RGBA8,
		RGBA16,
		RGBA16F,
		RGBA32F,

		//Depth
		DEPTH,
		DEPTH24STENCIL8,
		DEPTH32FSTENCIL8
	};
	enum class TextureWrap
	{
		REPEAT,
		MIRRORED_REPEAT,
		CLAMP_TO_EDGE,
		CLAMP_TO_BORDER
	};
	enum class TextureFilter
	{
		NEAREST,
		LINEAR
	};

	class VORTEX_API Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetID() const = 0;
		virtual uint64_t GetBindlessHandle() const = 0;
		virtual const char* GetPath() const = 0;

		virtual glm::vec2 GetSize() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual void MakeHandleResident() const = 0;
		virtual void MakeHandleNonResident() const = 0;
		virtual void SetData(void* data, uint32_t size) = 0;
		virtual uint32_t* GetData() = 0;
	};

	class VORTEX_API Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const uint32_t width, const uint32_t height);
		static Ref<Texture2D> Create(const std::string& path, TextureFormat format = TextureFormat::AUTO, TextureWrap wrap = TextureWrap::REPEAT, TextureFilter filter = TextureFilter::NEAREST);
	};

	class VORTEX_API Texture3D : public Texture
	{
	public:
		static Ref<Texture3D> Create(const uint32_t width, const uint32_t height);
		static Ref<Texture3D> Create(const std::string& path, TextureFormat format = TextureFormat::AUTO, TextureWrap wrap = TextureWrap::REPEAT, TextureFilter filter = TextureFilter::NEAREST);
	};
}
