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

		void SetParent(Object& parent)
		{
			VORTEX_ASSERT(parent.HasComponent<TransformComponent>(), "Transform's Parent doesn't have TransformComponent!");
			m_Parent = MakeRef<Object>(parent);
			m_Parent->GetComponent<TransformComponent>().m_ChildCount++;
		}

		void Move(const glm::vec3& delta)
		{
			SetPosition(m_Position + delta);
		}
		void Rotate(const glm::vec3& delta)
		{
			SetRotation(m_Rotation + delta);
		}
		void Scale(const glm::vec3& delta)
		{
			SetScale(m_Scale + delta);
		}
		void RotateAround(const glm::vec3& position, const glm::vec3& axis, const float radius, const float angle)
		{
			m_Position = position;

			m_Origin = radius * (glm::vec3(1.f) - axis);
			Rotate(axis * angle);
		}
		
		void SetPosition(const glm::vec3& position)
		{
			if (position == m_Position) return;
			m_Position = position;

			b_Updated = false;
		}
		void SetRotation(const glm::vec3& rotation)
		{
			if (rotation == m_Rotation) return;
			m_Rotation = rotation;

			b_Updated = false;
		}
		void SetScale(const glm::vec3& scale)
		{
			if (scale == m_Scale) return;
			m_Scale = scale;

			b_Updated = false;
		}
		void SetOrigin(const glm::vec3& origin)
		{
			m_Origin = origin;
		}

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetRotation() const { return m_Rotation; }
		const glm::vec3& GetScale() const { return m_Scale; }
		const glm::vec3& GetOrigin() const { return m_Origin; }

		const glm::mat4& GetTransformMatrix() { Update();  return m_TransformMatrix; }

		const TransformComponent* GetParent() { return m_Parent ? &m_Parent->GetComponent<TransformComponent>() : nullptr; }

		void Reset()
		{
			m_TransformMatrix = glm::mat4(1.f);
			m_Position = glm::vec3(0.f);
			m_Rotation = glm::vec3(0.f);
			m_Scale = glm::vec3(1.f);
		    m_Origin = glm::vec3(0.f);
		}

	private:
		void Update()
		{
			if ((b_Updated && !m_Parent) || (b_Updated && (m_Parent && m_Parent->GetComponent<TransformComponent>().m_OutdatedChildCount == 0))) return;

			if (m_OutdatedChildCount == 0) m_OutdatedChildCount = m_ChildCount;

			m_TransformMatrix = glm::mat4(1.0f);

			m_TransformMatrix = glm::translate(m_TransformMatrix, m_Position)
				* glm::scale(m_TransformMatrix, m_Scale)
				* glm::rotate(m_TransformMatrix, glm::radians(m_Rotation.x), glm::vec3(1, 0, 0))
				* glm::rotate(m_TransformMatrix, glm::radians(m_Rotation.y), glm::vec3(0, 1, 0))
				* glm::rotate(m_TransformMatrix, glm::radians(m_Rotation.z), glm::vec3(0, 0, 1))
				* glm::translate(m_TransformMatrix, m_Origin);

			if (m_Parent)
			{
				auto& parentTransform = m_Parent->GetComponent<TransformComponent>();
				m_TransformMatrix = parentTransform.GetTransformMatrix() * m_TransformMatrix;
				parentTransform.m_OutdatedChildCount--;
			}

			b_Updated = true;
		}

	private:
		glm::vec3 m_Position = glm::vec3(0.f);
		glm::vec3 m_Rotation = glm::vec3(0.f);
		glm::vec3 m_Scale = glm::vec3(1.f);
		glm::vec3 m_Origin = glm::vec3(0.f);

		glm::mat4 m_TransformMatrix = glm::mat4(1.f);
		bool b_Updated = true;

		Ref<Object> m_Parent = nullptr;
		uint32_t m_ChildCount = 0;
		uint32_t m_OutdatedChildCount = 0;
	};

	struct CameraComponent
	{
	public:
		CameraComponent(const CameraType type, const glm::vec2& rectSize, const float zNear, const float zFar, const float fov = 60.f) : m_CameraZNear(zNear), m_CameraZFar(zFar) { m_Camera = Camera::Create(type, rectSize.x, rectSize.y, zNear, zFar, fov); }
		CameraComponent(const CameraComponent&) = default;

		void SetZoom(const float zoom) { m_Camera->SetZoom(zoom); }

		const glm::mat4& GetProjectionMatrix() { return m_Camera->GetProjectionMatrix(); }
		const glm::mat4& GetViewMatrix(const glm::vec3& position, const glm::vec3& rotation) { UpdateClipSpace(position); return m_Camera->GetViewMatrix(position, rotation); }
		const glm::mat4& GetViewProjectionMatrix(const glm::vec3& position, const glm::vec3& rotation) { UpdateClipSpace(position);  return m_Camera->GetViewProjectionMatrix(position, rotation); }

		const glm::vec4& GetRect() { return m_Camera->GetRect(); }

		void OnEvent(Event& e) { m_Camera->OnEvent(e); }

	private:
		void UpdateClipSpace(const glm::vec3& position)
		{
			glm::vec2 clipSpace = m_Camera->GetClipSpace();
			clipSpace = glm::vec2(m_CameraZNear, m_CameraZFar) + position.z;
			m_Camera->SetClipSpace(clipSpace.x, clipSpace.y);
		}

	private:
		Ref<Camera> m_Camera;

		float m_CameraZNear, m_CameraZFar;
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