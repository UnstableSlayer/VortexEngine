#include "vpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Vortex
{
	/// Camera ////////////////////////////////////

	Ref<Camera> Camera::Create(const CameraType type, const float width, const float height, const float zNear, const float zFar, const float fov)
	{
		switch (type)
		{
		case CameraType::Orthographic: return MakeRef<OrthographicCamera>(width, height, zNear, zFar, fov);
		case CameraType::Perspective: return MakeRef<PerspectiveCamera>(width, height, zNear, zFar, fov);
		}

		VORTEX_NO_CONDITION_ASSERT("Invalid Camera Type!");
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



	/// Orthographic ////////////////////////////////////

	OrthographicCamera::OrthographicCamera(float width, float height, float zNear, float zFar, float fov)
	{
		m_ProjectionMatrix = glm::ortho(-width, width, -height, height, zNear, zFar);
		m_ViewMatrix = glm::mat4(1.0f);

		m_AspectRatio = width / height;
		m_Rect = { -width, width, -height, height };
		m_Near = zNear;
		m_Far = zFar;
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

	

	/// Perspective ////////////////////////////////////

	PerspectiveCamera::PerspectiveCamera(float width, float height, float zNear, float zFar, float fov)
	{
		m_ProjectionMatrix = glm::perspectiveFov(fov, width, height, zNear, zFar);
		m_ViewMatrix = glm::mat4(1.0f);

		m_AspectRatio = width / height;
		m_Rect = { -width, width, -height, height };
		m_Near = zNear;
		m_Far = zFar;
		m_FOV = fov;
	}

	void PerspectiveCamera::SetZoom(const float zoom)
	{
		m_Zoom = std::max(zoom, 0.1f);
		m_Rect = { -m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom };
		m_ProjectionMatrix = glm::ortho(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom, -1.f, 10.f);
	}

	void PerspectiveCamera::Resize(const float width, const float height)
	{
		m_AspectRatio = width / height;

		m_Rect = { -m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom };
		m_ProjectionMatrix = glm::ortho(m_Rect.x, m_Rect.y, m_Rect.z, m_Rect.w, m_Near, m_Far);
	}

	void PerspectiveCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(VORTEX_BIND_EVENT(PerspectiveCamera::OnWindowResize));
	}
	bool PerspectiveCamera::OnWindowResize(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();

		m_Rect = { -m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom };
		m_ProjectionMatrix = glm::perspectiveFov(m_FOV, m_Rect.y, m_Rect.w, m_Near, m_Far);

		return false;
	}


}