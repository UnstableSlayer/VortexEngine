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
		const aiScene* scene = importer.ReadFile(path, aiProcess_CalcTangentSpace
			| aiProcess_PreTransformVertices
			| aiProcess_JoinIdenticalVertices
			| aiProcess_ImproveCacheLocality
			| aiProcess_LimitBoneWeights
			| aiProcess_RemoveRedundantMaterials
			| aiProcess_SplitLargeMeshes
			| aiProcess_Triangulate
			| aiProcess_GenUVCoords
			| aiProcess_SortByPType
			| aiProcess_FindDegenerates
			| aiProcess_FindInvalidData
			| 0);
		
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			VORTEX_CORE_ERROR("Assimp can't load object: {0}", importer.GetErrorString());
			return;
		}

		VORTEX_CORE_WARNING("SHITTY IMPLEMENTATION OF ASSIMP GONNA LOAD ONLY FIRST MESH");
		aiMesh* mesh = scene->mMeshes[0];

		VORTEX_ASSERT(mesh, "NO MESH IN FILE");

		float* vertices = new float[mesh->mNumVertices * 3 * 2];
		for (size_t i = 0; i < mesh->mNumVertices; i++)
		{
			*(vertices + i * 6) = mesh->mVertices[i].x;
			*(vertices + i * 6 + 1) = mesh->mVertices[i].y;
			*(vertices + i * 6 + 2) = mesh->mVertices[i].z;

			if (mesh->HasNormals())
			{
				*(vertices + i * 6 + 3) = mesh->mNormals[i].x;
				*(vertices + i * 6 + 4) = mesh->mNormals[i].y;
				*(vertices + i * 6 + 5) = mesh->mNormals[i].z;
			}
		}
		m_Vertices = VertexBuffer::Create(vertices, mesh->mNumVertices * 3 * 2 * sizeof(vertices));
		m_Vertices->SetLayout({
				{ShaderDataType::Vec3f, "aPos"},
				{ShaderDataType::Vec3f, "aNormal"}
			});

		uint32_t* indices = new uint32_t[mesh->mNumFaces * 3];
		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; j++)
			{
				VORTEX_ASSERT(face.mNumIndices == 3, "Face Indices more than 3!");
				*(indices + i * 3 + j) = face.mIndices[j];
			}
		}
		m_Indices = IndexBuffer::Create(indices, mesh->mNumFaces * 3);
	}
}