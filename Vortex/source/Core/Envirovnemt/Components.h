#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Core/Renderer/Texture.h"
#include "Core/Renderer/SubTexture2D.h"

namespace Vortex
{
	struct TagComponent
	{
	public:
		TagComponent(const char* tag) : m_Tag(tag) {}
		TagComponent(const TagComponent&) = default;

	public:
		const char* m_Tag;
	};

	struct TransformComponent
	{
	public:
		TransformComponent() { Reset(); }
		TransformComponent(const TransformComponent&) = default;
		
		void Move(glm::vec3 delta)
		{
			SetPosition(m_Position + delta);
		}

		void Rotate(glm::vec3 delta)
		{
			SetRotation(m_Rotation + delta);
		}

		void Scale(glm::vec3 delta)
		{
			SetScale(m_Scale + delta);
		}

		void SetPosition(glm::vec3 position)
		{
			if (position == m_Position) return;

			m_Position = position;
			b_Updated = false;
		}

		void SetRotation(glm::vec3 rotation)
		{
			if (rotation == m_Rotation) return;

			m_Rotation = rotation;
			b_Updated = false;
		}

		void SetScale(glm::vec3 scale)
		{
			if (scale == m_Scale) return;

			m_Scale = scale;
			b_Updated = false;
		}

		const glm::vec3& GetPosition() { return m_Position; }
		const glm::vec3& GetRotation() { return m_Rotation; }
		const glm::vec3& GetScale() { return m_Scale; }

		const glm::mat4& GetTransformMatrix() { Update();  return m_TransformMatrix; }

		void Reset()
		{
			m_TransformMatrix = glm::mat4(1.f);
			m_Position = glm::vec3(0.f);
			m_Rotation = glm::vec3(0.f);
			m_Scale = glm::vec3(1.f);
		}

	private:
		void Update()
		{
			if (b_Updated) return;

			m_TransformMatrix = glm::mat4(1.0f);

			m_TransformMatrix = glm::translate(m_TransformMatrix, m_Position)
				* glm::scale(m_TransformMatrix, m_Scale)
				* glm::rotate(m_TransformMatrix, glm::radians(m_Rotation.x), glm::vec3(1, 0, 0))
				* glm::rotate(m_TransformMatrix, glm::radians(m_Rotation.y), glm::vec3(0, 1, 0))
				* glm::rotate(m_TransformMatrix, glm::radians(m_Rotation.z), glm::vec3(0, 0, 1));

			b_Updated = true;
		}

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;

		glm::mat4 m_TransformMatrix;
		bool b_Updated = true;
	};

	struct SpriteComponent
	{
	public:
		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;

		SpriteComponent(Ref<Texture2D> sprite, glm::vec2 textureTiling = glm::vec2(1.f), glm::vec4 tint = glm::vec4(1.f))
			: m_Sprite(sprite), m_TextureTiling(textureTiling), m_Tint(tint) {}

	public:
		Ref<Texture2D> m_Sprite;
		glm::vec2 m_TextureTiling = glm::vec2(1.f);
		glm::vec4 m_Tint = glm::vec4(1.f);

		bool IsVisible = true;
	};

	struct SubSpriteComponent
	{
	public:
		SubSpriteComponent() = default;
		SubSpriteComponent(const SubSpriteComponent&) = default;

		SubSpriteComponent(Ref<SubTexture2D> sprite, glm::vec4 tint = glm::vec4(1.f))
			: m_Sprite(sprite), m_Tint(tint) {}

	public:
		Ref<SubTexture2D> m_Sprite;
		glm::vec4 m_Tint = glm::vec4(1.f);

		bool IsVisible = true;
	};

}