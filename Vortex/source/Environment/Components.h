#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Environment/Object.h"
//#include "Renderer/Texture.h"
//#include "Renderer/Buffers.h"

namespace Vortex
{
	struct TagComponent
	{
		const char* m_Tag;
	};

	struct TransformComponent
	{
		glm::vec3 m_Position = glm::vec3(0.f);
		glm::quat m_Rotation = glm::quat(1.f, 0.f, 0.f, 0.f);
		glm::vec3 m_Scale = glm::vec3(1.f);
		glm::vec3 m_Origin = glm::vec3(0.f);

		glm::mat4 m_TransformMatrix = glm::mat4(1.f);
		bool m_Updated = true;

		Object m_Parent;
		uint32_t m_ChildCount = 0;
		uint32_t m_OutdatedChildCount = 0;
	};

	enum class CameraType
    {
        Orthographic,
        Perspective
    };

	struct CameraComponent
	{
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.f);
		glm::mat4 m_ViewMatrix = glm::mat4(1.f);
		glm::mat4 m_ViewProjectionMatrix = glm::mat4(1.f);

		float m_Near, m_Far;

		float m_AspectRatio;
		float m_Zoom;
		float m_FOV;
		CameraType m_CameraType;
	};
/*
	struct SpriteComponent
	{
		Ref<Texture2D> m_Texture;
		glm::vec2 m_TextureTiling = glm::vec2(1.f);
		glm::vec4 m_Tint = glm::vec4(1.f);

		bool IsVisible = true;
	};

	struct SubSpriteComponent
	{
		glm::vec2 m_TexCoords[4];
		glm::vec2 m_TexSize = glm::vec2(1.f);
		glm::vec4 m_Tint = glm::vec4(1.f);

		bool IsVisible = true;
	};

	struct TileMapData
	{
		std::unordered_map<char, SubSpriteComponent> m_TileDictionary;
		std::string m_TileMap;

		Ref<Texture2D> m_AtlasTexture;

		uint32_t m_MapWidth;
	};

	struct MeshData 
	{
		Ref<VertexArray>* m_Data;
		size_t m_Count;
	};

	struct MaterialData 
	{
		Ref<Shader> m_Shader;
		Ref<Texture> m_Texture;
	};

	struct StaticMeshComponent
	{
		MeshData mesh;
		MaterialData material;
	};
*/
}
