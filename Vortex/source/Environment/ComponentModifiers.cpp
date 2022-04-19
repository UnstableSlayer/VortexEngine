#include "vpch.h"
#include "ComponentModifiers.h"

namespace Vortex
{
    void Transform::Move(TransformComponent &t, const glm::vec3 &deltaPos)
    {
        Transform::SetPosition(t, t.m_Position + deltaPos);
    }

    void Transform::Rotate(TransformComponent& t, const glm::quat &deltaRot)
    {
        Transform::SetRotation(t, deltaRot * t.m_Rotation);
    }

    void Transform::Rotate(TransformComponent &t, const glm::vec3 &deltaRot)
    {
        Transform::SetRotation(t, glm::quat(glm::radians(deltaRot)) * t.m_Rotation);
    }

    void Transform::RotateAround(TransformComponent &t, const glm::vec3 &origin, const glm::vec3 &axis, const float radius, const float deltaAngle)
    {
        t.m_Position = origin;

		t.m_Origin = radius * (glm::vec3(1.f) - axis);
		Transform::Rotate(t, axis * deltaAngle);

    }

    void Transform::Scale(TransformComponent &t, const glm::vec3 &deltaScale)
    {
        Transform::SetScale(t, t.m_Scale + deltaScale);
    }

    void Transform::SetPosition(TransformComponent &t, const glm::vec3 &pos)
    {
        if (pos == t.m_Position) return;

        t.m_Position = pos;
		t.m_Updated = false;
    }

    void Transform::SetRotation(TransformComponent &t, const glm::quat &rot)
    {
        if (rot == t.m_Rotation) return;

        t.m_Rotation = rot;
		t.m_Updated = false;
    }

    void Transform::SetScale(TransformComponent &t, const glm::vec3 &scale)
    {
        if (scale == t.m_Scale) return;

        t.m_Scale = scale;
		t.m_Updated = false;
    }

    void Transform::SetParent(TransformComponent &t, Object &parentObj)
    {
        VORTEX_ASSERT(parentObj.HasComponent<TransformComponent>(), "Parent doesn't have TransformComponent!");
		t.m_Parent = MakeRef<Object>(parentObj);
		t.m_Parent->GetComponent<TransformComponent>().m_ChildCount++;
    }

    void Transform::SetOrigin(TransformComponent &t, const glm::vec3 &origin)
    {
        t.m_Origin = origin;
    }

    void Transform::UpdateTransformMatrix(TransformComponent &t)
    {
        if ((t.m_Updated && !t.m_Parent) || (t.m_Updated && t.m_Parent->GetComponent<TransformComponent>().m_OutdatedChildCount == 0)) return;

        if (t.m_OutdatedChildCount == 0) t.m_OutdatedChildCount = t.m_ChildCount;

        t.m_TransformMatrix = glm::mat4(1.f);

		t.m_TransformMatrix = glm::translate(t.m_TransformMatrix, t.m_Position)
			* glm::scale(t.m_TransformMatrix, t.m_Scale)
			* glm::toMat4(t.m_Rotation)
			* glm::translate(t.m_TransformMatrix, t.m_Origin);

		if (t.m_Parent)
		{
			auto& parentTransform = t.m_Parent->GetComponent<TransformComponent>();
			t.m_TransformMatrix = parentTransform.m_TransformMatrix * t.m_TransformMatrix;
			parentTransform.m_OutdatedChildCount--;
		}

		t.m_Updated = true;
    }

    void Transform::Reset(TransformComponent &t)
    {
        t.m_TransformMatrix = glm::mat4(1.f);
		t.m_Position = glm::vec3(0.f);
		t.m_Rotation = glm::quat(1.f, 0.f, 0.f, 0.f);
		t.m_Scale = glm::vec3(1.f);
		t.m_Origin = glm::vec3(0.f);
    }

    void Camera::OrthographicInit(CameraComponent& camera, float width, float height, float zNear, float zFar, float fov)
    {
        camera.m_AspectRatio = width / height;
		camera.m_Zoom = 1.f;
		camera.m_Near = zNear;
		camera.m_Far = zFar;

		camera.m_ProjectionMatrix = glm::ortho(-camera.m_AspectRatio * camera.m_Zoom, camera.m_AspectRatio * camera.m_Zoom, -camera.m_Zoom, camera.m_Zoom,
											camera.m_Near, camera.m_Far);
		camera.m_ViewMatrix = glm::mat4(1.0f);
    }

    void Camera::OrthographicZoom(CameraComponent& camera, const float zoom)
    {
        camera.m_Zoom = std::max(zoom, 0.1f);
		camera.m_ProjectionMatrix = glm::ortho(-camera.m_AspectRatio * camera.m_Zoom, camera.m_AspectRatio * camera.m_Zoom, -camera.m_Zoom, camera.m_Zoom,
			camera.m_Near, camera.m_Far);
    }

    void Camera::OrthographicResize(CameraComponent& camera, const float width, const float height)
    {
        camera.m_AspectRatio = width / height;
		camera.m_ProjectionMatrix = glm::ortho(-camera.m_AspectRatio * camera.m_Zoom, camera.m_AspectRatio * camera.m_Zoom, -camera.m_Zoom, camera.m_Zoom,
			camera.m_Near, camera.m_Far);
    }

    void Camera::PerspectiveInit(CameraComponent& camera, float width, float height, float zNear, float zFar, float fov)
    {
        camera.m_AspectRatio = width / height;
		camera.m_Zoom = 1.f;
		camera.m_Near = zNear;
		camera.m_Far = zFar;
		camera.m_FOV = fov;

		camera.m_ProjectionMatrix = glm::perspective(-camera.m_FOV, camera.m_AspectRatio, camera.m_Near, camera.m_Far);
		camera.m_ViewMatrix = glm::mat4(1.0f);
    }

    void Camera::PerspectiveZoom(CameraComponent& camera, const float zoom)
    {
        camera.m_Zoom = zoom < 1.f ? 1.f : zoom;
		camera.m_ProjectionMatrix = glm::perspective(-glm::atan(glm::tan(camera.m_FOV) / (camera.m_Zoom * 10.f)), camera.m_AspectRatio, camera.m_Near, camera.m_Far);
    }

    void Camera::PerspectiveResize(CameraComponent& camera, const float width, const float height)
    {
        camera.m_AspectRatio = width / height;
		camera.m_ProjectionMatrix = glm::perspective(-glm::atan(glm::tan(camera.m_FOV) / (camera.m_Zoom * 10.f)), camera.m_AspectRatio, camera.m_Near, camera.m_Far);
    }

    void Camera::RecalculateViewMatrix(CameraComponent& camera, const glm::vec3& position, const glm::quat& rotation)
    {
        camera.m_ViewMatrix = glm::toMat4(rotation) * glm::translate(glm::mat4(1.0f), -position);
		camera.m_ViewProjectionMatrix = camera.m_ProjectionMatrix * camera.m_ViewMatrix;
    }
}
