#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Core/Renderer/Camera.h"
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

		void SetParent(TransformComponent* parent)
		{
			m_ParentTransform = parent;
		}

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
			m_Position = position;

			b_Updated = false;
		}
		void SetRotation(glm::vec3 rotation)
		{
			m_Rotation = rotation;

			b_Updated = false;
		}
		void SetScale(glm::vec3 scale)
		{
			m_Scale = scale;

			b_Updated = false;
		}

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetRotation() const { return m_Rotation; }
		const glm::vec3& GetScale() const { return m_Scale; }

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
			if ((m_ParentTransform && m_ParentTransform->b_ParentUpdated && b_Updated) || (!m_ParentTransform && b_Updated)) return;

			m_TransformMatrix = glm::mat4(1.0f);

			m_TransformMatrix = glm::translate(m_TransformMatrix, m_Position)
				* glm::scale(m_TransformMatrix, m_Scale)
				* glm::rotate(m_TransformMatrix, glm::radians(m_Rotation.x), glm::vec3(1, 0, 0))
				* glm::rotate(m_TransformMatrix, glm::radians(m_Rotation.y), glm::vec3(0, 1, 0))
				* glm::rotate(m_TransformMatrix, glm::radians(m_Rotation.z), glm::vec3(0, 0, 1));

			if (m_ParentTransform)
				m_TransformMatrix = m_ParentTransform->GetTransformMatrix() * m_TransformMatrix;

			b_Updated = true;
			b_ParentUpdated = !b_ParentUpdated;
		}
	protected:
		bool b_ParentUpdated = true;

	private:
		glm::vec3 m_Position = glm::vec3(0.f);
		glm::vec3 m_Rotation = glm::vec3(0.f);
		glm::vec3 m_Scale = glm::vec3(1.f);

		glm::mat4 m_TransformMatrix = glm::mat4(1.f);
		TransformComponent* m_ParentTransform = nullptr;

		bool b_Updated = true;
	};

	struct CameraComponent
	{
	public:
		CameraComponent(const CameraType type, const glm::vec2& rectSize, const float min, const float max) { m_Camera = Camera::Create(type, rectSize.x, rectSize.y, min, max); }
		CameraComponent(const CameraComponent&) = default;

		void SetZoom(const float zoom) { m_Camera->SetZoom(zoom); }

		const glm::mat4& GetProjectionMatrix() { return m_Camera->GetProjectionMatrix(); }
		const glm::mat4& GetViewMatrix(const glm::vec3& position, const glm::vec3& rotation) { return m_Camera->GetViewMatrix(position, rotation); }
		const glm::mat4& GetViewProjectionMatrix(const glm::vec3& position, const glm::vec3& rotation) { return m_Camera->GetViewProjectionMatrix(position, rotation); }

		const glm::vec4& GetRect() { return m_Camera->GetRect(); }

		void OnEvent(Event& e) { m_Camera->OnEvent(e); }

	private:
		Ref<Camera> m_Camera;
	};

	struct SpriteComponent
	{
	public:
		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;

		SpriteComponent(Ref<Texture2D> sprite, glm::vec2 textureTiling = glm::vec2(1.f), glm::vec4 tint = glm::vec4(1.f))
			: m_Texture(sprite), m_TextureTiling(textureTiling), m_Tint(tint) {}

	public:
		Ref<Texture2D> m_Texture;
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