#include "assimp/material.h"
#include "assimp/types.h"
#include "vpch.h"
#include "ComponentModifiers.h"

//#include "Renderer/Buffers.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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
        if (t.m_Updated && (!t.m_Parent || t.m_Parent.GetComponent<TransformComponent>().m_OutdatedChildCount == 0))
            return;

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

    extern void Camera::RecalculateViewMatrix(CameraComponent& camera, TransformComponent& transform)
    {
        camera.m_ViewMatrix = glm::inverse(transform.m_TransformMatrix); // glm::toMat4(rotation)* glm::translate(glm::mat4(1.0f), -position);
		camera.m_ViewProjectionMatrix = camera.m_ProjectionMatrix * camera.m_ViewMatrix;
    }

    extern bool Camera::OnWindowResize(WindowResizeEvent& e, CameraComponent& camera)
	{
		if ((float)e.GetWidth() == 0 || (float)e.GetHeight() == 0) return false;
		camera.m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();

        if(camera.m_CameraType == CameraType::Orthographic)
            camera.m_ProjectionMatrix = glm::ortho(-camera.m_AspectRatio * camera.m_Zoom, camera.m_AspectRatio * camera.m_Zoom,
                                                   -camera.m_Zoom, camera.m_Zoom, camera.m_Near, camera.m_Far);
        else if(camera.m_CameraType == CameraType::Perspective)
            camera.m_ProjectionMatrix = glm::perspective(-glm::atan(glm::tan(camera.m_FOV) / (camera.m_Zoom * 10.f)), 
                                                    camera.m_AspectRatio, camera.m_Near, camera.m_Far);

		return false;
	}

    //////////////////////////////////////////////////////


    /// SubSprite ////////////////////////////////////////

/*    extern void SubSprite::Create(SubSpriteComponent &subSprite, Ref<Texture2D> atlasTexture, const glm::vec2 &min, const glm::vec2 &max)
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

    //////////////////////////////////////////////////////


    /// TileMap //////////////////////////////////////////

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
    
    //////////////////////////////////////////////////////


    /// Mesh /////////////////////////////////////////////

    extern void Mesh::LoadMeshData(MeshData& meshData, const char* path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_Fast);
    
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            VORTEX_CORE_ERROR("Assimp can't load object: {0}", importer.GetErrorString());
            return;
        }
    
        BufferLayout bufferLayout = {
                {ShaderDataType::Vec3f, "aPos"},
                {ShaderDataType::Vec3f, "aNormal"},
                {ShaderDataType::Vec2f, "aTexCoord"}
        };
        uint32_t vertexLayoutFloatCount = bufferLayout.GetStride() / sizeof(float);
        meshData.m_Count = scene->mNumMeshes;
        meshData.m_Data = new Ref<VertexArray>[scene->mNumMeshes];
        
        for (size_t m = 0; m < scene->mNumMeshes; m++)
        {
            aiMesh* mesh = scene->mMeshes[m];
            meshData.m_Data[m] = VertexArray::Create();

            VORTEX_ASSERT(mesh, "NO MESH IN FILE");

            std::vector<float> vertices;
            for (size_t i = 0; i < mesh->mNumVertices; i++)
            {
                vertices.push_back(mesh->mVertices[i].x);
                vertices.push_back(mesh->mVertices[i].y);
                vertices.push_back(mesh->mVertices[i].z);

                if (mesh->HasNormals())
                {
                    vertices.push_back(mesh->mNormals[i].x);
                    vertices.push_back(mesh->mNormals[i].y);
                    vertices.push_back(mesh->mNormals[i].z);
                }

                if (mesh->HasTextureCoords(0))
                {
                    vertices.push_back(mesh->mTextureCoords[0][i].x);
                    vertices.push_back(mesh->mTextureCoords[0][i].y);
                }
            }

            Ref<VertexBuffer> m_Vertices = VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float));
            m_Vertices->SetLayout(bufferLayout);

            meshData.m_Data[m]->AddVertexBuffer(m_Vertices);

            std::vector<uint32_t> indices;
            uint32_t indexOffset = 0;
            uint32_t max = 0;
            for (size_t i = 0; i < mesh->mNumFaces; i++)
            {
                aiFace face = mesh->mFaces[i];
                for (size_t j = 0; j < face.mNumIndices; j++)
                {
                    VORTEX_ASSERT(face.mNumIndices == 3, "Face Indices more than 3!");
                    indices.push_back(face.mIndices[j] + indexOffset);

                    if (face.mIndices[j] + indexOffset > max)
                        max = face.mIndices[j] + indexOffset;
                }
            }
            indexOffset = max + vertexLayoutFloatCount - max % vertexLayoutFloatCount;

            Ref<IndexBuffer> m_Indices = IndexBuffer::Create(indices.data(), indices.size());
            meshData.m_Data[m]->SetIndexBuffer(m_Indices);
        }

        VORTEX_CORE_INFO("Number of materials: {0}", scene->mNumMaterials);
        for(size_t i; i < scene->mNumMaterials; i++) {
            aiMaterial* material = scene->mMaterials[i];
            aiString mPath;
            if(material->GetTexture(aiTextureType_DIFFUSE, 0, &mPath, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
                VORTEX_CORE_INFO("Loaded Texture: {0}", mPath.C_Str());
        }
    }

    extern void Mesh::GenPlaneMesh(MeshData& meshData, float width, float height, float uvScaleX, float uvScaleY)
    {
        float* vertices = new float[] {
            -width, 0.f, -height,     0.f, 1.f, 0.f,     0.f,      0.f,
             width, 0.f, -height,     0.f, 1.f, 0.f,     uvScaleX, 0.f,
             width, 0.f,  height,     0.f, 1.f, 0.f,     uvScaleX, uvScaleY,
            -width, 0.f,  height,     0.f, 1.f, 0.f,     0.f,      uvScaleY
        };
        uint32_t* indices = new uint32_t[]{
             0, 1, 2,
             2, 3, 0
        };
       
        meshData.m_Data = new Ref<VertexArray>();
        *meshData.m_Data = VertexArray::Create();
        meshData.m_Count = 1;

        Ref<VertexBuffer> m_Vertices = VertexBuffer::Create(vertices, 32 * sizeof(float));
        m_Vertices->SetLayout({
                {ShaderDataType::Vec3f, "aPos"},
                {ShaderDataType::Vec3f, "aNormal"},
                {ShaderDataType::Vec2f, "aTexCoord"}
            });
        meshData.m_Data[0]->AddVertexBuffer(m_Vertices);

        Ref<IndexBuffer> m_Indices = IndexBuffer::Create(indices, 6);
        meshData.m_Data[0]->SetIndexBuffer(m_Indices);
    }

    extern void Mesh::GenPlaneMeshFromPoints(MeshData& meshData, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, uint32_t subdivision) 
    {
        glm::vec3 vec03 = (v3 - v0) / (float)subdivision;
        glm::vec3 vec12 = (v2 - v1) / (float)subdivision;

        int vertexCount = (subdivision + 1) * (subdivision + 1);
        float* vertices = new float[vertexCount * 8];
        uint32_t* indices = new uint32_t[subdivision * subdivision * 6];


        uint32_t vertIndex = 0;
        uint32_t trisIndex = 0;

        for (size_t row = 0; row < subdivision + 1; row++)
        {
            glm::vec3 start = v0 + vec03 * (float)row;
            glm::vec3 end = v1 + vec12 * (float)row;
            glm::vec3 vectorSubdiv = (end - start) / (float)subdivision;

            for (size_t col = 0; col < subdivision + 1; col++)
            {
                glm::vec3 vertex = start + vectorSubdiv * (float)col;
                glm::vec2 uv = glm::vec2((float)col / subdivision, (float)row / subdivision);

                glm::vec3 tangent = glm::normalize(vertex);
                glm::vec3 nextStart = start + vec03;
                glm::vec3 nextEnd = end + vec12;
                glm::vec3 nextVectorSubdiv = (nextEnd - nextStart) / (float)subdivision;
                glm::vec3 nextRowVertex = nextStart + nextVectorSubdiv * (float)col;
                glm::vec3 possibleBitangent = glm::normalize(nextRowVertex - vertex);
                glm::vec3 normal = glm::cross(nextRowVertex, possibleBitangent);

                vertices[vertIndex++] = vertex.x;
                vertices[vertIndex++] = vertex.y;
                vertices[vertIndex++] = vertex.z;

                vertices[vertIndex++] = normal.x;
                vertices[vertIndex++] = normal.y;
                vertices[vertIndex++] = normal.z;

                vertices[vertIndex++] = uv.x;
                vertices[vertIndex++] = uv.y;

                if (col == subdivision || row == subdivision)
                {
                    continue;
                }

                int index = row * (subdivision + 1) + col;

                indices[trisIndex++] = index;
                indices[trisIndex++] = index + subdivision + 2;
                indices[trisIndex++] = index + subdivision + 1;
                indices[trisIndex++] = index;
                indices[trisIndex++] = index + 1;
                indices[trisIndex++] = index + subdivision + 2;
            }
        }

        meshData.m_Data = new Ref<VertexArray>();
        *meshData.m_Data = VertexArray::Create();
        meshData.m_Count = 1;

        Ref<VertexBuffer> m_Vertices = VertexBuffer::Create(vertices, vertIndex * sizeof(float));
        m_Vertices->SetLayout({
                {ShaderDataType::Vec3f, "aPos"},
                {ShaderDataType::Vec3f, "aNormal"},
                {ShaderDataType::Vec2f, "aTexCoord"}
            });
        meshData.m_Data[0]->AddVertexBuffer(m_Vertices);

        Ref<IndexBuffer> m_Indices = IndexBuffer::Create(indices, trisIndex);
        meshData.m_Data[0]->SetIndexBuffer(m_Indices);
    }


    extern void Mesh::GenCubeMesh(MeshData& meshData)
    {
    }


*/
    //////////////////////////////////////////////////////
}
