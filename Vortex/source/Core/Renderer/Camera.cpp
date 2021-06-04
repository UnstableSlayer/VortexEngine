#include "vpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Vortex
{
	//glm::perspective(2.0f, 1.0f, 0.1f, 100.0f)
	//glm::ortho(left, right, bottom, top, -1.f, 10.f)

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.f, 10.f)), m_ViewMatrix(glm::mat4(1.0f)), m_AspectRatio(right/top)
	{
		RecalculateViewMatrix();
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), -m_Position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(-m_Rotation.x), glm::vec3(1, 0, 0))
			* glm::rotate(glm::mat4(1.0f), glm::radians(-m_Rotation.y), glm::vec3(0, 1, 0))
			* glm::rotate(glm::mat4(1.0f), glm::radians(-m_Rotation.z), glm::vec3(0, 0, 1));

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::Resize(const float width, const float height)
	{
		m_AspectRatio = width / height;

		m_ProjectionMatrix = glm::ortho(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom, -1.f, 10.f);
		RecalculateViewMatrix();
	}

	bool OrthographicCamera::OnWindowResize(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();

		m_ProjectionMatrix = glm::ortho(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom, -1.f, 10.f);
		RecalculateViewMatrix();

		return false;
	}
}