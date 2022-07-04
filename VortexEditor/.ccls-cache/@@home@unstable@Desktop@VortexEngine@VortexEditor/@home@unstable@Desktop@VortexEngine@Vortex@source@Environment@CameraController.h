#include "Components.h"
#include "ComponentModifiers.h"

#include "Events/WindowEvents.h"

namespace Vortex
{
    enum class CameraType
    {
        Orthographic,
        Perspective
    };

    class VORTEX_API CameraController
    {
    public:
        CameraController(const CameraType type, const float width, const float height, const float zNear = 0.1f, const float zFar = 1000.f, const float fov = 60.f);
        CameraController(CameraComponent camera, const CameraType cameraType) : m_Camera(camera) {}
        CameraController(const CameraController&) = default;
        virtual ~CameraController() = default;

        virtual void OnEvent(Event& e);

    protected:
    	virtual bool OrthographicOnWindowResize(WindowResizeEvent& event);
        virtual bool PerspectiveOnWindowResize(WindowResizeEvent& event);

    public:
        CameraComponent m_Camera;
        CameraType m_CameraType;
    };
}
