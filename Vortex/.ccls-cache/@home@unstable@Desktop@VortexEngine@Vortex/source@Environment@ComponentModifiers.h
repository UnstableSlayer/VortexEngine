#pragma once
#include "Components.h"

namespace Vortex
{
    class VORTEX_API Transform
    {
        public:
        static void Move(TransformComponent& t, const glm::vec3& deltaPos);
        static void Rotate(TransformComponent& t, const glm::quat& deltaRot);
        static void Rotate(TransformComponent& t, const glm::vec3& deltaRot);
        static void RotateAround(TransformComponent& t, const glm::vec3& origin, const glm::vec3& axis, const float radius, const float deltaAngle);
        static void Scale(TransformComponent& t, const glm::vec3& deltaScale);
        static void SetPosition(TransformComponent& t, const glm::vec3& pos);
        static void SetRotation(TransformComponent& t, const glm::quat& rot);
        static void SetScale(TransformComponent& t, const glm::vec3& scale);
        static void SetParent(TransformComponent& t, Object& parentObj);
        static void SetOrigin(TransformComponent& t, const glm::vec3& origin);
        static void UpdateTransformMatrix(TransformComponent& t);
        static void Reset(TransformComponent& t);
    };

    class VORTEX_API Camera
    {
    public:
        static void OrthographicInit(CameraComponent& camera, float width, float height, float zNear, float zFar, float fov);
        static void OrthographicZoom(CameraComponent& camera, const float zoom);
        static void OrthographicResize(CameraComponent& camera, const float width, const float height);

        static void PerspectiveInit(CameraComponent& camera, float width, float height, float zNear, float zFar, float fov);
        static void PerspectiveZoom(CameraComponent& camera, const float zoom);
        static void PerspectiveResize(CameraComponent& camera, const float width, const float height);

        static void RecalculateViewMatrix(CameraComponent& camera, const glm::vec3& position, const glm::quat& rotation);
    };
}
