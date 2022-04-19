#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Object.h"
#include "Renderer/Texture.h"
#include "Renderer/SubTexture2D.h"

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

		Ref<Object> m_Parent = nullptr;
		uint32_t m_ChildCount = 0;
		uint32_t m_OutdatedChildCount = 0;
	};

	struct CameraComponent
	{
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		float m_Near, m_Far;

		float m_AspectRatio;
		float m_Zoom;
		float m_FOV;
	};

	struct SpriteComponent
	{
		Ref<Texture2D> m_Texture;
		glm::vec2 m_TextureTiling = glm::vec2(1.f);
		glm::vec4 m_Tint = glm::vec4(1.f);

		bool IsVisible = true;
	};

	struct SubSpriteComponent
	{
		Ref<SubTexture2D> m_Sprite;
		glm::vec4 m_Tint = glm::vec4(1.f);

		bool IsVisible = true;
	};

}
