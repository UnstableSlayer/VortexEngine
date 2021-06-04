#pragma once
#include "../Events/WindowEvents.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Vortex
{
	enum class CameraTypes
	{
		Orthographical = 0,
		Perspective
	};

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetRotation() const { return m_Rotation; }

		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
		void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		void SetZoom(const float zoom) 
		{
			m_Zoom = zoom;
			m_ProjectionMatrix = glm::ortho(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom, -1.f, 10.f);
		}

		const glm::vec4& GetRect() const { 
			return { -m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom }; 
		}

		void OnEvent(Event &e)
		{
			EventDispatcher dispatcher(e);
			dispatcher.Dispatch<WindowResizeEvent>(VORTEX_BIND_EVENT(OrthographicCamera::OnWindowResize));
		}

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();
		bool OnWindowResize(WindowResizeEvent& event);

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = glm::vec3(0.f);
		glm::vec3 m_Rotation = glm::vec3(0.f);

		float m_AspectRatio;
		float m_Zoom = 1.f;
	};
}