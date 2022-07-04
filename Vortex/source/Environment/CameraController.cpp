#include <vpch.h>
#include "CameraController.h"

#include "Events/Event.h"

namespace Vortex
{
    CameraController::CameraController(const CameraType type, const float width, const float height, const float zNear, const float zFar, const float fov)
	{
        CameraComponent camera;

		switch (type)
		{
		case CameraType::Orthographic:
            Camera::OrthographicInit(camera, width, height, zNear, zFar, fov);
            m_Camera = camera;
            m_CameraType = type;
            return;

        case CameraType::Perspective:
            Camera::PerspectiveInit(camera, width, height, zNear, zFar, fov);
            m_Camera = camera;
            m_CameraType = type;
            return;
        }

		VORTEX_ASSERT(false, "Invalid Camera Type!");
	}

    void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
        switch(m_CameraType)
        {
        case CameraType::Orthographic:
            dispatcher.Dispatch<WindowResizeEvent>(VORTEX_BIND_EVENT(CameraController::OrthographicOnWindowResize));
            break;
        case CameraType::Perspective:
            dispatcher.Dispatch<WindowResizeEvent>(VORTEX_BIND_EVENT(CameraController::PerspectiveOnWindowResize));
            break;
        }
    }

    bool CameraController::OrthographicOnWindowResize(WindowResizeEvent& e)
	{
		if ((float)e.GetWidth() == 0 || (float)e.GetHeight() == 0) return false;
		m_Camera.m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();

		m_Camera.m_ProjectionMatrix = glm::ortho(-m_Camera.m_AspectRatio * m_Camera.m_Zoom, m_Camera.m_AspectRatio * m_Camera.m_Zoom, -m_Camera.m_Zoom, m_Camera.m_Zoom,
											m_Camera.m_Near, m_Camera.m_Far);

		return false;
	}

	bool CameraController::PerspectiveOnWindowResize(WindowResizeEvent& e)
	{
		if ((float)e.GetWidth() == 0 || (float)e.GetHeight() == 0) return false;
		m_Camera.m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();

		m_Camera.m_ProjectionMatrix = glm::perspective(-glm::atan(glm::tan(m_Camera.m_FOV) / (m_Camera.m_Zoom * 10.f)), m_Camera.m_AspectRatio,
                                            m_Camera.m_Near, m_Camera.m_Far);

		return false;
	}
}
