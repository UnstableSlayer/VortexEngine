#include "vpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Vortex
{
	Ref<Camera> Camera::Create(const CameraType type, const float width, const float height, const float min, const float max)
	{
		switch (type)
		{
		case CameraType::Orthographical: return MakeRef<OrthographicCamera>(width, height, min, max); break;
		case CameraType::Perspective: return nullptr;
		}

		return nullptr;
	}

	void Camera::RecalculateViewMatrix(const glm::vec3& position, const glm::vec3& rotation)
	{
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), -position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(-rotation.x), glm::vec3(1, 0, 0))
			* glm::rotate(glm::mat4(1.0f), glm::radians(-rotation.y), glm::vec3(0, 1, 0))
			* glm::rotate(glm::mat4(1.0f), glm::radians(-rotation.z), glm::vec3(0, 0, 1));

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}



	OrthographicCamera::OrthographicCamera(float width, float height, float min, float max)
	{
		m_ProjectionMatrix = glm::ortho(-width, width, -height, height, min, max);
		m_ViewMatrix = glm::mat4(1.0f);

		m_AspectRatio = width / height;
		m_Rect = { -width, width, -height, height };
		m_Near = min;
		m_Far = max;
	}

	void OrthographicCamera::SetZoom(const float zoom)
	{
		m_Zoom = std::max(zoom, 0.1f);
		m_Rect = { -m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom };
		m_ProjectionMatrix = glm::ortho(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom, -1.f, 10.f);
	}

	void OrthographicCamera::Resize(const float width, const float height)
	{
		m_AspectRatio = width / height;

		m_Rect = { -m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom };
		m_ProjectionMatrix = glm::ortho(m_Rect.x, m_Rect.y, m_Rect.z, m_Rect.w, m_Near, m_Far);
	}

	void OrthographicCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(VORTEX_BIND_EVENT(OrthographicCamera::OnWindowResize));
	}
	bool OrthographicCamera::OnWindowResize(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();

		m_Rect = { -m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom };
		m_ProjectionMatrix = glm::ortho(m_Rect.x, m_Rect.y, m_Rect.z, m_Rect.w, m_Near, m_Far);

		return false;
	}
}