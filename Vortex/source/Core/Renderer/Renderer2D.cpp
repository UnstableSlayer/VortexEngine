#include "vpch.h"
#include "Renderer2D.h"

#include "../Core.h"
#include "RenderCommand.h"

#include "Buffers.h"
#include "Shader.h"
#include "../Time.h"

#include <glm/gtc/type_ptr.hpp>


namespace Vortex
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		glm::vec2 TexTiling = glm::vec2(1.0f);
		float TexIndex = 0.f;
	};

	struct Renderer2DData
	{
		static const uint32_t MaxQuads = 10000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;

		Ref<Shader> DefaultShader;
		Ref<Texture2D> DefaultTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> Textures;
		uint32_t TextureSlotIndex = 1;

		std::array<Ref<TransformComponent>, MaxQuads> TransformMatrices;



		Renderer2D::Statistics Stats;
	};
	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Vec3f, "aPos" },
			{ ShaderDataType::Vec4f, "aColor" },
			{ ShaderDataType::Vec2f, "aTexCoord" },
			{ ShaderDataType::Vec2f, "aTexTiling" },
			{ ShaderDataType::Float, "aTexIndex" }
		});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		uint32_t textureData = 0xffffffff;
		s_Data.DefaultTexture = Texture2D::Create(1, 1);
		s_Data.DefaultTexture->SetData(&textureData, sizeof(uint32_t));

		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
		{
			samplers[i] = i;
		}

		s_Data.DefaultShader = Shader::Create("Shaders/FlatColor.glsl");
		s_Data.DefaultShader->Bind();
		s_Data.DefaultShader->SetUniformInt("uTexture", 0);
		s_Data.DefaultShader->SetUniformVec2("uTextureScale", glm::vec2(1.f));
		s_Data.DefaultShader->SetUniformIntArray("uTextures", samplers, s_Data.MaxTextureSlots);

		s_Data.Textures[0] = s_Data.DefaultTexture;
	}
	void Renderer2D::Destroy()
	{
		delete s_Data.QuadVertexBufferPtr;
		delete s_Data.QuadVertexBufferBase;
	}


	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data.DefaultShader->Bind();
		s_Data.DefaultShader->SetUniformMat4("uViewProj", camera.GetViewProjectionMatrix());

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;

		Renderer2D::ResetStats();
	}
	void Renderer2D::EndScene()
	{
		uint32_t size = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, size);

		Flush();
	}

	void Renderer2D::Flush()
	{
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
			s_Data.Textures[i]->Bind(i);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
	
		s_Data.Stats.DrawCalls++;
	}


	void Renderer2D::DrawQuad(TransformComponent& transform, const glm::vec4& color)
	{
		if (s_Data.QuadIndexCount >= s_Data.MaxIndices)
			FlushAndReset();

		s_Data.QuadVertexBufferPtr->Position = transform.GetTransformMatrix() * glm::vec4(-0.5f, -0.5f, 0.f, 1.f);
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.f, 0.f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = transform.GetTransformMatrix() * glm::vec4(0.5f, -0.5f, 0.f, 1.f);
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.f, 0.f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = transform.GetTransformMatrix() * glm::vec4(0.5f, 0.5f, 0.f, 1.f);
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.f, 1.f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = transform.GetTransformMatrix() * glm::vec4(-0.5f, 0.5f, 0.f, 1.f);
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.f, 1.f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}
	void Renderer2D::DrawQuad(TransformComponent& transform, const Ref<Texture2D>& texture, const glm::vec2& texTiling, const glm::vec4& tint)
	{	
		if (s_Data.QuadIndexCount >= s_Data.MaxIndices)
			FlushAndReset();

		float textureIndex = 0.f;

		for (size_t i = 0; i < s_Data.TextureSlotIndex; i++)
		{
			if (s_Data.Textures[i]->GetID() == texture->GetID())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.f)
		{
			textureIndex = (float)s_Data.TextureSlotIndex;

			s_Data.Textures[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		s_Data.QuadVertexBufferPtr->Position = transform.GetTransformMatrix() * glm::vec4(-0.5f, -0.5f, 0.f, 1.f);
		s_Data.QuadVertexBufferPtr->Color = tint;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.f, 0.f };
		s_Data.QuadVertexBufferPtr->TexTiling = texTiling;
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = transform.GetTransformMatrix() * glm::vec4(0.5f, -0.5f, 0.f, 1.f);
		s_Data.QuadVertexBufferPtr->Color = tint;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.f, 0.f };
		s_Data.QuadVertexBufferPtr->TexTiling = texTiling;
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = transform.GetTransformMatrix() * glm::vec4(0.5f, 0.5f, 0.f, 1.f);
		s_Data.QuadVertexBufferPtr->Color = tint;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.f, 1.f };
		s_Data.QuadVertexBufferPtr->TexTiling = texTiling;
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = transform.GetTransformMatrix() * glm::vec4(-0.5f, 0.5f, 0.f, 1.f);
		s_Data.QuadVertexBufferPtr->Color = tint;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.f, 1.f };
		s_Data.QuadVertexBufferPtr->TexTiling = texTiling;
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}

	void Renderer2D::DrawFromSpriteSheet(TransformComponent& transform, const Texture2D& spriteSheet, const glm::vec2 spriteSize, const glm::vec2 spriteCoord, const glm::vec4& tint)
	{
	}

	void Renderer2D::FlushAndReset()
	{
		EndScene();

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;

		Renderer2D::ResetStats();
	}



	void Renderer2D::ResetStats()
	{
		memset(&s_Data.Stats, 0, sizeof(Statistics));
	}
	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_Data.Stats;
	}
}