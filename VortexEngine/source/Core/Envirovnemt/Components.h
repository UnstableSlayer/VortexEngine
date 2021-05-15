#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Vortex
{
	struct TransformComponent
	{
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		
		void Move(glm::vec3 delta)
		{
			m_TransformMatrix = glm::translate(m_TransformMatrix, delta);
			m_Position += delta;
		}

		void Rotate(glm::vec3 delta)
		{
			m_Rotation += delta;

			Update();
		}

		void Scale(glm::vec3 delta)
		{
			SetScale(m_Scale - delta);
		}

		void SetPosition(glm::vec3 position)
		{
			Move(position - m_Position);
		}

		void SetRotation(glm::vec3 rotation)
		{
			Rotate(rotation - m_Rotation);
		}

		void SetScale(glm::vec3 scale)
		{
			if (scale.x < 0 || scale.y < 0 || scale.z < 0) return;

			m_Scale = scale;
			Update();
		}

		const glm::mat4& GetTransformMatrix() { return m_TransformMatrix; }

		void Reset()
		{
			m_TransformMatrix = glm::mat4(0.f);
			m_Position = glm::vec3(0.f);
			m_Rotation = glm::vec3(0.f);
			m_Scale = glm::vec3(0.f);
		}

	private:
		void Update()
		{
			m_TransformMatrix = glm::mat4(1.0f);

			m_TransformMatrix = glm::scale(m_TransformMatrix, m_Scale)
				* glm::rotate(m_TransformMatrix, glm::radians(m_Rotation.x), glm::vec3(1, 0, 0))
				* glm::rotate(m_TransformMatrix, glm::radians(m_Rotation.y), glm::vec3(0, 1, 0))
				* glm::rotate(m_TransformMatrix, glm::radians(m_Rotation.z), glm::vec3(0, 0, 1))
				* glm::translate(m_TransformMatrix, m_Position);
		}

	public:
		glm::vec3 m_Position = glm::vec3(0.f);
		glm::vec3 m_Rotation = glm::vec3(0.f);
		glm::vec3 m_Scale = glm::vec3(1.f);

	private:
		glm::mat4 m_TransformMatrix = glm::mat4(1.0f);
	};

	struct RendererComponent
	{

	};

	struct CameraComponent
	{

	};
}