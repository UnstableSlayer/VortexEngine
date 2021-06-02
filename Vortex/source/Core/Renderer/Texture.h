#pragma once
#include "../Core.h"
#include <string>

namespace Vortex
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetID() const = 0;
		virtual const char* GetPath() const = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual void SetData(void* data, uint32_t size) = 0;
		virtual unsigned int* GetData() = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const uint32_t width, const uint32_t height);
		static Ref<Texture2D> Create(const std::string& path);
	};
}
