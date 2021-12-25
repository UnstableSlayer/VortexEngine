#include "vpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

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

		VORTEX_ASSERT(false, "Invalid Camera Type!");
		return nullptr;
	}

	void Camera::RecalculateViewMatrix(const glm::vec3& position, const glm::quat& rotation)
	{
		m_ViewMatrix = glm::toMat4(rotation) * glm::translate(glm::mat4(1.0f), -position);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}



	/// Orthographic ////////////////////////////////////

	OrthographicCamera::OrthographicCamera(float width, float height, float zNear, float zFar, float fov)
	{
		m_AspectRatio = width / height;
		m_Zoom = 1.f;
		m_Near = zNear;
		m_Far = zFar;

		m_ProjectionMatrix = glm::ortho(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom,
											m_Near, m_Far);
		m_ViewMatrix = glm::mat4(1.0f);
	}

	void OrthographicCamera::SetZoom(const float zoom)
	{
		m_Zoom = std::max(zoom, 0.1f);
		m_ProjectionMatrix = glm::ortho(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom,
			m_Near, m_Far);
	}

	void OrthographicCamera::Resize(const float width, const float height)
	{
		m_AspectRatio = width / height;
		m_ProjectionMatrix = glm::ortho(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom,
			m_Near, m_Far);
	}

	void OrthographicCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(VORTEX_BIND_EVENT(OrthographicCamera::OnWindowResize));
	}
	bool OrthographicCamera::OnWindowResize(WindowResizeEvent& e)
	{
		if ((float)e.GetWidth() == 0 || (float)e.GetHeight() == 0) return false;
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		
		m_ProjectionMatrix = glm::ortho(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom,
											m_Near, m_Far);

		return false;
	}

	

	/// Perspective ////////////////////////////////////

	PerspectiveCamera::PerspectiveCamera(float width, float height, float zNear, float zFar, float fov)
	{
		m_AspectRatio = width / height;
		m_Zoom = 1.f;
		m_Near = zNear;
		m_Far = zFar;
		m_FOV = fov;

		m_ProjectionMatrix = glm::perspective(-m_FOV, m_AspectRatio, m_Near, m_Far);
		m_ViewMatrix = glm::mat4(1.0f);
	}

	void PerspectiveCamera::SetZoom(const float zoom)
	{
		m_Zoom = zoom < 1.f ? 1.f : zoom;
		m_ProjectionMatrix = glm::perspective(-glm::atan(glm::tan(m_FOV) / (m_Zoom * 10.f)), m_AspectRatio, m_Near, m_Far);
	}

	void PerspectiveCamera::SetFOV(const float fov)
	{
		m_FOV = fov;
		m_ProjectionMatrix = glm::perspective(-glm::atan(glm::tan(m_FOV) / (m_Zoom * 10.f)), m_AspectRatio, m_Near, m_Far);
	}

	void PerspectiveCamera::Resize(const float width, const float height)
	{
		m_AspectRatio = width / height;

		m_ProjectionMatrix = glm::perspective(-glm::atan(glm::tan(m_FOV) / (m_Zoom * 10.f)), m_AspectRatio, m_Near, m_Far);
	}

	void PerspectiveCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(VORTEX_BIND_EVENT(PerspectiveCamera::OnWindowResize));
	}
	bool PerspectiveCamera::OnWindowResize(WindowResizeEvent& e)
	{
		if ((float)e.GetWidth() == 0 || (float)e.GetHeight() == 0) return false;
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();

		m_ProjectionMatrix = glm::perspective(-glm::atan(glm::tan(m_FOV) / (m_Zoom * 10.f)), m_AspectRatio, m_Near, m_Far);

		return false;
	}

}