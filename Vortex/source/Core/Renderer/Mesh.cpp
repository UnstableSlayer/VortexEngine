#include "vpch.h"
#include "Mesh.h"
#include "vpch.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Vortex
{
	void Mesh::Load(const std::string& path)
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

		m_Data = VertexArray::Create();

		std::vector<uint32_t> indices;
		uint32_t indexOffset = 0;
		for (size_t m = 0; m < scene->mNumMeshes; m++)
		{
			aiMesh* mesh = scene->mMeshes[m];

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
			VORTEX_CORE_INFO("Vertices[{0}]: {1}", m, vertices.size());

			Ref<VertexBuffer> m_Vertices = VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(float));
			m_Vertices->SetLayout(bufferLayout);

			m_Data->AddVertexBuffer(m_Vertices);

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
		}

		VORTEX_CORE_INFO("Indices: {0}", indices.size());

		Ref<IndexBuffer> m_Indices = IndexBuffer::Create(indices.data(), indices.size());
		m_Data->SetIndexBuffer(m_Indices);
	}
}