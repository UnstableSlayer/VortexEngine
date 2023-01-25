#include "vpch.h"
#include "ComponentModifiers.h"

#include "Renderer/Buffers.h"
#include <string>

namespace Vortex
{
    /// Transform ////////////////////////////////////////

    extern void Transform::Move(TransformComponent& t, const glm::vec3 &deltaPos)
    {
        Transform::SetPosition(t, t.m_Position + deltaPos);
    }

    extern void Transform::Rotate(TransformComponent& t, const glm::quat &deltaRot)
    {
        Transform::SetRotation(t, deltaRot * t.m_Rotation);
    }

    extern void Transform::Rotate(TransformComponent& t, const glm::vec3 &deltaRot)
    {
        Transform::SetRotation(t, glm::quat(glm::radians(deltaRot)) * t.m_Rotation);
    }

    extern void Transform::RotateAround(TransformComponent& t, const glm::vec3 &origin, const glm::vec3 &axis, const float radius, const float deltaAngle)
    {
        //t.m_Position = origin;

		t.m_Origin = radius * (glm::vec3(1.f) - axis);
		Transform::Rotate(t, axis * deltaAngle);

    }

    extern void Transform::Scale(TransformComponent &t, const glm::vec3 &deltaScale)
    {
        Transform::SetScale(t, t.m_Scale + deltaScale);
    }

    extern void Transform::SetPosition(TransformComponent& t, const glm::vec3 &pos)
    {
        if (pos == t.m_Position) return;

        t.m_Position = pos;
		t.m_Updated = false;
    }

    extern void Transform::SetRotation(TransformComponent& t, const glm::quat &rot)
    {
        if (rot == t.m_Rotation) return;

        t.m_Rotation = rot;
		t.m_Updated = false;
    }

    extern void Transform::SetScale(TransformComponent &t, const glm::vec3 &scale)
    {
        if (scale == t.m_Scale) return;

        t.m_Scale = scale;
		t.m_Updated = false;
    }

    extern void Transform::SetParent(TransformComponent &t, Object &parentObj)
    {
        VORTEX_ASSERT(parentObj.HasComponent<TransformComponent>(), "Parent doesn't have TransformComponent!");
		t.m_Parent = parentObj;
		t.m_Parent.GetComponent<TransformComponent>().m_ChildCount++;
    }

    extern void Transform::SetOrigin(TransformComponent &t, const glm::vec3 &origin)
    {
        t.m_Origin = origin;
    }

    extern void Transform::UpdateTransformMatrix(TransformComponent &t)
    {
        if ((t.m_Updated && !t.m_Parent) || (t.m_Updated && t.m_Parent.GetComponent<TransformComponent>().m_OutdatedChildCount == 0)) return;
        if(t.m_Updated) return;

        if (t.m_OutdatedChildCount == 0) t.m_OutdatedChildCount = t.m_ChildCount;

        t.m_TransformMatrix = glm::mat4(1.f);

		t.m_TransformMatrix = glm::translate(t.m_TransformMatrix, t.m_Position)
			* glm::scale(t.m_TransformMatrix, t.m_Scale)
			* glm::toMat4(t.m_Rotation)
			* glm::translate(t.m_TransformMatrix, t.m_Origin);

		if (t.m_Parent)
		{
			auto& parentTransform = t.m_Parent.GetComponent<TransformComponent>();
			t.m_TransformMatrix = parentTransform.m_TransformMatrix * t.m_TransformMatrix;
			parentTransform.m_OutdatedChildCount--;
		}

		t.m_Updated = true;
    }

    extern void Transform::Reset(TransformComponent &t)
    {
        t.m_TransformMatrix = glm::mat4(1.f);
		t.m_Position = glm::vec3(0.f);
		t.m_Rotation = glm::quat(1.f, 0.f, 0.f, 0.f);
		t.m_Scale = glm::vec3(1.f);
		t.m_Origin = glm::vec3(0.f);
    }

    //////////////////////////////////////////////////////


    /// Camera ///////////////////////////////////////////

    extern void Camera::Init(CameraComponent& camera, const CameraType type, const float width, const float height, const float zNear, const float zFar, const float fov)
    {
        camera.m_AspectRatio = width / height;
		camera.m_Zoom = 1.f;
		camera.m_Near = zNear;
		camera.m_Far = zFar;
		camera.m_FOV = fov;
        camera.m_CameraType = type;

        if(camera.m_CameraType == CameraType::Orthographic)
            camera.m_ProjectionMatrix = glm::ortho(-camera.m_AspectRatio * camera.m_Zoom, camera.m_AspectRatio * camera.m_Zoom, -camera.m_Zoom, camera.m_Zoom,
                                                   camera.m_Near, camera.m_Far);
        else if(camera.m_CameraType == CameraType::Perspective)
            camera.m_ProjectionMatrix = glm::perspective(-camera.m_FOV, camera.m_AspectRatio, camera.m_Near, camera.m_Far);

		camera.m_ViewMatrix = glm::mat4(1.0f);
    }

    extern void Camera::OrthographicZoom(CameraComponent& camera, const float zoom)
    {
        camera.m_Zoom = std::max(zoom, std::numeric_limits<float>::min());
		camera.m_ProjectionMatrix = glm::ortho(-camera.m_AspectRatio * camera.m_Zoom, camera.m_AspectRatio * camera.m_Zoom, -camera.m_Zoom, camera.m_Zoom,
			camera.m_Near, camera.m_Far);
    }

    extern void Camera::OrthographicResize(CameraComponent& camera, const float width, const float height)
    {
        camera.m_AspectRatio = width / height;
		camera.m_ProjectionMatrix = glm::ortho(-camera.m_AspectRatio * camera.m_Zoom, camera.m_AspectRatio * camera.m_Zoom, -camera.m_Zoom, camera.m_Zoom,
			camera.m_Near, camera.m_Far);
    }

    extern void Camera::PerspectiveZoom(CameraComponent& camera, const float zoom)
    {
        camera.m_Zoom = std::max(zoom, std::numeric_limits<float>::min());
		camera.m_ProjectionMatrix = glm::perspective(-camera.m_FOV, camera.m_AspectRatio, camera.m_Near, camera.m_Far);
    }

    extern void Camera::PerspectiveResize(CameraComponent& camera, const float width, const float height)
    {
        camera.m_AspectRatio = width / height;
		camera.m_ProjectionMatrix = glm::perspective(-camera.m_FOV, camera.m_AspectRatio, camera.m_Near, camera.m_Far);
    }

    extern void Camera::RecalculateViewMatrix(CameraComponent& camera, const glm::vec3& position, const glm::quat& rotation)
    {
        camera.m_ViewMatrix = glm::toMat4(rotation) * glm::translate(glm::mat4(1.0f), -position);
		camera.m_ViewProjectionMatrix = camera.m_ProjectionMatrix * camera.m_ViewMatrix;
    }

    extern bool Camera::OnWindowResize(WindowResizeEvent& e, CameraComponent& camera)
	{
		if ((float)e.GetWidth() == 0 || (float)e.GetHeight() == 0) return false;
		camera.m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();

        if(camera.m_CameraType == CameraType::Orthographic)
            camera.m_ProjectionMatrix = glm::ortho(-camera.m_AspectRatio * camera.m_Zoom, camera.m_AspectRatio * camera.m_Zoom, -camera.m_Zoom, camera.m_Zoom,
                                                   camera.m_Near, camera.m_Far);
        else if(camera.m_CameraType == CameraType::Perspective)
            camera.m_ProjectionMatrix = glm::perspective(-glm::atan(glm::tan(camera.m_FOV) / (camera.m_Zoom * 10.f)), camera.m_AspectRatio,
                                            camera.m_Near, camera.m_Far);

		return false;
	}

    //////////////////////////////////////////////////////


    /// SubSprite ////////////////////////////////////////

    extern void SubSprite::Create(SubSpriteComponent &subSprite, Ref<Texture2D> atlasTexture, const glm::vec2 &min, const glm::vec2 &max)
    {
        //subSprite.m_AtlasTexture = atlasTexture;
        subSprite.m_TexSize = (max - min) * atlasTexture->GetSize();

        subSprite.m_TexCoords[0] = { min.x, min.y };
		subSprite.m_TexCoords[1] = { max.x, min.y };
		subSprite.m_TexCoords[2] = { max.x, max.y };
		subSprite.m_TexCoords[3] = { min.x, max.y };
    }

	extern void SubSprite::CreateWithCells(SubSpriteComponent& subSprite, Ref<Texture2D> atlasTexture, const glm::vec2& spriteCellPos, const glm::vec2& cellSize, const glm::vec2& spriteSizeInCells)
	{
		const glm::vec2 atlasSize = atlasTexture->GetSize();

		const glm::vec2 min = { (spriteCellPos.x * cellSize.x) / atlasSize.x, (spriteCellPos.y * cellSize.y) / atlasSize.y };
		const glm::vec2 max = { ((spriteCellPos.x + spriteSizeInCells.x) * cellSize.x) / atlasSize.x, ((spriteCellPos.y + spriteSizeInCells.y) * cellSize.y) / atlasSize.y };

		//subSprite.m_AtlasTexture = atlasTexture;
        subSprite.m_TexSize = (max - min) * atlasTexture->GetSize();

		subSprite.m_TexCoords[0] = { min.x, min.y };
		subSprite.m_TexCoords[1] = { max.x, min.y };
		subSprite.m_TexCoords[2] = { max.x, max.y };
		subSprite.m_TexCoords[3] = { min.x, max.y };
	}

   extern SpriteComponent TileMap::GenUnifiedTileMap(TileMapData &data)
   {
       std::string flattenTileMap = data.m_TileMap;
       flattenTileMap.erase(std::remove(flattenTileMap.begin(), flattenTileMap.end(), '\n'), flattenTileMap.cend());

       uint32_t texWidth = 0, texHeight = 0;
       for (int y = 0; y < flattenTileMap.length() / data.m_MapWidth; y++)
       {
           uint32_t minHeight = -1;
           uint32_t minWidth = 0;
           for(int x = 0; x < data.m_MapWidth; x++)
           {
               char chr = flattenTileMap[y * data.m_MapWidth + x];
               auto& subSprite = data.m_TileDictionary[chr];
               //VORTEX_CORE_INFO("SubSprite[{0}]: {1}x{2}", flattenTileMap[y * data.m_MapWidth + x], subSprite.m_TexSize.x, subSprite.m_TexSize.y);
               minWidth += subSprite.m_TexSize.x;
               minHeight = std::min(minHeight, (uint32_t)subSprite.m_TexSize.y);
           }
           texWidth = std::max(texWidth, minWidth);
           texHeight+=minHeight;
       }

       //VORTEX_CORE_INFO("FinalTexSize: {0}x{1}", texWidth, texHeight);
       uint32_t* texData = new uint32_t[texWidth * texHeight];

       uint32_t* atlasData = data.m_AtlasTexture->GetData();
       uint32_t currentPixelX = 0, currentPixelY = 0;
       for(int charY = flattenTileMap.length() / data.m_MapWidth - 1; charY >= 0; charY--)
       {
           uint32_t minHeight = -1;
           for(int charX = 0; charX < data.m_MapWidth; charX++)
           {
               char chr = flattenTileMap[charY * data.m_MapWidth + charX];
               auto& subSprite = data.m_TileDictionary[chr];

               uint32_t subSpriteX = subSprite.m_TexCoords[0].x * data.m_AtlasTexture->GetSize().x;
               uint32_t subSpriteY = subSprite.m_TexCoords[0].y * data.m_AtlasTexture->GetSize().y;

               for (int y = 0; y < subSprite.m_TexSize.y; y++) {
                   for(int x = 0; x < subSprite.m_TexSize.x; x++)
                   {
                       uint32_t index = (uint32_t)((subSpriteY + y) * data.m_AtlasTexture->GetSize().x + (subSpriteX + x));
                       //VORTEX_CORE_WARNING("atlas[{0}x{1}]====>texData[{2}x{3}] == {4}", subSpriteX + x, subSpriteY + y, currentPixelX + x, currentPixelY + y, *(atlasData + index));
                       if(index > 0 && index < data.m_AtlasTexture->GetSize().x * data.m_AtlasTexture->GetSize().y)
                           texData[(currentPixelY + y) * texWidth + currentPixelX + x] = *(atlasData + index);// + 0x001001001000;
                       else
                           texData[(currentPixelY + y) * texWidth + currentPixelX + x] = 0;
                   }
               }
               currentPixelX += subSprite.m_TexSize.x;
               minHeight = std::min(minHeight, (uint32_t)subSprite.m_TexSize.y);
           }
           currentPixelX = 0;
           currentPixelY += minHeight;
       }

       delete [] atlasData;

       SpriteComponent result;
       result.m_Texture = Texture2D::Create(texWidth, texHeight);
       result.m_Texture->SetData(texData, sizeof(uint32_t) * texWidth * texHeight);

       return result;
   }
}
