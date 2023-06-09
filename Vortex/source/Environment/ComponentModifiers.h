#pragma once
#include "Components.h"
#include "Events/WindowEvents.h"

namespace Vortex
{
    namespace Transform
    {
        extern void Move(TransformComponent& t, const glm::vec3& deltaPos);
        extern void Rotate(TransformComponent& t, const glm::quat& deltaRot);
        extern void Rotate(TransformComponent& t, const glm::vec3& deltaRot);
        extern void RotateAround(TransformComponent& t, const glm::vec3& origin, const glm::vec3& axis, const float radius, const float deltaAngle);
        extern void Scale(TransformComponent& t, const glm::vec3& deltaScale);
        extern void SetPosition(TransformComponent& t, const glm::vec3& pos);
        extern void SetRotation(TransformComponent& t, const glm::quat& rot);
        extern void SetScale(TransformComponent& t, const glm::vec3& scale);
        extern void SetParent(TransformComponent& t, Object& parentObj);
        extern void SetOrigin(TransformComponent& t, const glm::vec3& origin);
        extern void UpdateTransformMatrix(TransformComponent& t);
        extern void Reset(TransformComponent& t);
    }

    namespace Camera
    {
        extern void Init(CameraComponent& camera, const CameraType type, const float width, const float height, const float zNear = 0.1f, const float zFar = 1000.f, const float fov = 60.f);
        extern void OrthographicZoom(CameraComponent& camera, const float zoom);
        extern void OrthographicResize(CameraComponent& camera, const float width, const float height);

        extern void PerspectiveInit(CameraComponent& camera, const float width, const float height, const float zNear, const float zFar, const float fov);
        extern void PerspectiveZoom(CameraComponent& camera, const float zoom);
        extern void PerspectiveResize(CameraComponent& camera, const float width, const float height);

        extern void RecalculateViewMatrix(CameraComponent& camera, TransformComponent& transform);
        extern bool OnWindowResize(WindowResizeEvent& e, CameraComponent& camera);
    }

    namespace SubSprite
    {
        extern void Create(SubSpriteComponent& subSprite, Ref<Texture2D> atlasTexture, const glm::vec2& min, const glm::vec2& max);
        extern void CreateWithCells(SubSpriteComponent& subSprite, Ref<Texture2D> atlasTexture, const glm::vec2& spritePos, const glm::vec2& cellSize, const glm::vec2& spriteScale);
    }

    namespace TileMap
    {
        extern SpriteComponent GenUnifiedTileMap(TileMapData& data);
    }

    namespace Mesh
    {
        extern void LoadMeshData(MeshData& meshData, const char* path);
        extern void GenPlaneMesh(MeshData& meshData, float width, float height, float uvScaleX, float uvScaleY);
        extern void GenPlaneMeshFromPoints(MeshData& meshData, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, uint32_t subdivision);
        extern void GenCubeMesh(MeshData& meshData);
        //extern void GenUVSphereMesh(MeshData& meshData, const char* path);
        //extern void GenCubeSphereMesh(MeshData& meshData, const char* path);
        //extern void GenIsoSphereMesh(MeshData& meshData, const char* path);
    }
}