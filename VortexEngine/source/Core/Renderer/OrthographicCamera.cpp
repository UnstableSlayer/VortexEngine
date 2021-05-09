#include "vpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Vortex
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.f, 10.f)), m_ViewMatrix(glm::mat4(1.0f))
	{
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), -m_Position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(-m_Rotation.x), glm::vec3(1, 0, 0))
			* glm::rotate(glm::mat4(1.0f), glm::radians(-m_Rotation.y), glm::vec3(0, 1, 0))
			* glm::rotate(glm::mat4(1.0f), glm::radians(-m_Rotation.z), glm::vec3(0, 0, 1));

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}