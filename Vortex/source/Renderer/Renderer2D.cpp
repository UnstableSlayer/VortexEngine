#include "Platforms/OpenGL/OpenGLBuffers.h"
#include "Platforms/OpenGL/OpenGLShader.h"
#include "vpch.h"
#include "Renderer2D.h"

#include "Core/App.h"

#include "Renderer/RenderCommand.h"
#include "Renderer/Buffers.h"
#include "Renderer/Shader.h"

#include "Environment/ComponentModifiers.h"

namespace Vortex
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		glm::vec2 TexTiling = glm::vec2(1.0f);
        uint32_t TexIndex = 0;
    };

	struct Renderer2DData
	{
		static const uint32_t MaxQuads = 10000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32;

        Ref<Framebuffer> RendererFB;
        Ref<Shader> PostEffectsShader;
        Ref<VertexArray> RendererFBQuad;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;

		Ref<Shader> DefaultShader;
		Ref<Texture2D> DefaultTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> Textures;
		uint32_t TextureSlotIndex = 1;

		const glm::vec3* CameraPos = nullptr;

		Renderer2D::Statistics Stats;
	};
	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		//Renderer framebuffer and renderer quad init
        {
			FramebufferParams fbParams;
			fbParams.Width = App::Get().GetWindow().GetWindowWidth() / App::Get().GetWindow().GetPixelWidth();
			fbParams.Height = App::Get().GetWindow().GetWindowHeight() / App::Get().GetWindow().GetPixelHeight();

			s_Data.RendererFB = Framebuffer::Create(fbParams);
			s_Data.RendererFBQuad = VertexArray::Create();

			float* vertices = new float[]{
				-1.f, -1.f,  0.f,    0.f, 0.f,
				 1.f, -1.f,  0.f,    1.f, 0.f,
				 1.f,  1.f,  0.f,    1.f, 1.f,
				-1.f,  1.f,  0.f,    0.f, 1.f
			};
			Ref<VertexBuffer> fbVbo = VertexBuffer::Create(vertices, sizeof(vertices)* 5 * 4);
			fbVbo->SetLayout({
				{ ShaderDataType::Vec3f, "aPos" },
				{ ShaderDataType::Vec2f, "aTexCoord"}
			});
			s_Data.RendererFBQuad->AddVertexBuffer(fbVbo);
			delete[] vertices;

			uint32_t* indices = new uint32_t[]{
				0, 1, 2,
				2, 3, 0
			};

			Ref<IndexBuffer> fbIbo = IndexBuffer::Create(indices, 6);
			s_Data.RendererFBQuad->SetIndexBuffer(fbIbo);
			delete[] indices;

			s_Data.PostEffectsShader = Shader::Create("Shaders/PostEffectShader.glsl");
			s_Data.PostEffectsShader->Bind();
			s_Data.PostEffectsShader->SetUniformInt("uTexture", 0);
		}

		//Quad vao for batching, default shader and textures init
		{
    		s_Data.QuadVertexArray = VertexArray::Create();

		    s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
	    	s_Data.QuadVertexBuffer->SetLayout({
    			{ ShaderDataType::Vec3f, "aPos" },
    			{ ShaderDataType::Vec4f, "aColor" },
    			{ ShaderDataType::Vec2f, "aTexCoord" },
    			{ ShaderDataType::Vec2f, "aTexTiling" },
    			{ ShaderDataType::UInt, "aTexIndex" }
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

    		s_Data.DefaultShader = Shader::Create("Shaders/unlitSpriteShader.glsl");
    		s_Data.DefaultShader->Bind();
    		s_Data.DefaultShader->SetUniformInt("uTexture", 0);
    		s_Data.DefaultShader->SetUniformVec2("uTextureScale", glm::vec2(1.f));
    		s_Data.DefaultShader->SetUniformIntArray("uTextures", samplers, s_Data.MaxTextureSlots);

		    s_Data.Textures[0] = s_Data.DefaultTexture;
		}
	}
	void Renderer2D::Destroy()
	{
		delete s_Data.QuadVertexBufferPtr;
		delete s_Data.QuadVertexBufferBase;

		delete s_Data.CameraPos;
	}

	Ref<Framebuffer>& Renderer2D::GetRendererFramebuffer() { return s_Data.RendererFB; }

	void Renderer2D::BeginScene(CameraComponent& camera, TransformComponent& transform)
	{
		Transform::UpdateTransformMatrix(transform);
		Camera::RecalculateViewMatrix(camera, transform);

		s_Data.CameraPos = &transform.m_Position;

        s_Data.RendererFB->Bind();

		s_Data.DefaultShader->Bind();
		s_Data.DefaultShader->SetUniformMat4("uViewProj", camera.m_ViewProjectionMatrix);
 
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

        s_Data.RendererFB->UnBind();

		auto params = s_Data.RendererFB->GetParams();
		RenderCommand::SetViewport(0, 0,
								   App::Get().GetWindow().GetWindowWidth(),
								   App::Get().GetWindow().GetWindowHeight());
		RenderCommand::Clear();

		s_Data.PostEffectsShader->Bind();
		Texture2D::Create(s_Data.RendererFB->GetColorAttachmentID())->Bind();

		s_Data.RendererFBQuad->Bind();
		RenderCommand::DrawIndexed(s_Data.RendererFBQuad);
	}

	void Renderer2D::EndSceneAndRenderToFramebuffer(Ref<Framebuffer>& targetFB)
	{
	   	uint32_t size = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, size);

		Flush();

        s_Data.RendererFB->UnBind();

		targetFB->Bind();
		auto params = s_Data.RendererFB->GetParams();
		RenderCommand::SetViewport(0, 0,
								   App::Get().GetWindow().GetWindowWidth(),
								   App::Get().GetWindow().GetWindowHeight());
		RenderCommand::Clear();

		s_Data.PostEffectsShader->Bind();
		Texture2D::Create(s_Data.RendererFB->GetColorAttachmentID())->Bind();

		s_Data.RendererFBQuad->Bind();
		RenderCommand::DrawIndexed(s_Data.RendererFBQuad);
		targetFB->UnBind();
	}



	void Renderer2D::Flush()
	{
		s_Data.DefaultShader->Bind();
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
			s_Data.Textures[i]->Bind(i);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);

		s_Data.Stats.DrawCalls++;
	}
	void Renderer2D::FlushAndReset()
	{
		EndScene();

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::AppendSingleVertexData(const glm::vec3& position, const glm::vec4& color, const glm::vec2& texCoord, const glm::vec2& texTiling, int textureIndex)
	{
		s_Data.QuadVertexBufferPtr->Position = position;
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = texCoord;
		s_Data.QuadVertexBufferPtr->TexTiling = texTiling;
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;
	}



	void Renderer2D::DrawQuad(TransformComponent& transform, const glm::vec4& color)
	{
		if (s_Data.QuadIndexCount >= s_Data.MaxIndices)
			FlushAndReset();

		glm::vec3 position;

		Transform::UpdateTransformMatrix(transform);

		position = transform.m_TransformMatrix * glm::vec4(-0.5f, -0.5f, 0.f, 1.f);
		Renderer2D::AppendSingleVertexData(position, color, { 0.f, 0.f }, { 1.f, 1.f }, 0.f);

		position = transform.m_TransformMatrix * glm::vec4(0.5f, -0.5f, 0.f, 1.f);
		Renderer2D::AppendSingleVertexData(position, color, { 1.f, 0.f }, { 1.f, 1.f }, 0.f);

		position = transform.m_TransformMatrix * glm::vec4(0.5f, 0.5f, 0.f, 1.f);
		Renderer2D::AppendSingleVertexData(position, color, { 1.f, 1.f }, { 1.f, 1.f }, 0.f);

		position = transform.m_TransformMatrix * glm::vec4(-0.5f, 0.5f, 0.f, 1.f);
		Renderer2D::AppendSingleVertexData(position, color, { 0.f, 1.f }, { 1.f, 1.f }, 0.f);

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}
	void Renderer2D::DrawQuad(TransformComponent& transform, const SpriteComponent& sprite, const glm::vec4& tint)
	{
		if (s_Data.QuadIndexCount >= s_Data.MaxIndices)
			FlushAndReset();

		int textureIndex = 0;
		for (size_t i = 0; i < s_Data.TextureSlotIndex; i++)
		{
			if (s_Data.Textures[i]->GetID() == sprite.m_Texture->GetID())
			{
				textureIndex = i;
				break;
			}
		}

		if (textureIndex == 0)
		{
			textureIndex = s_Data.TextureSlotIndex;

			s_Data.Textures[s_Data.TextureSlotIndex] = sprite.m_Texture;
			s_Data.TextureSlotIndex++;
		}

		glm::vec3 position;

		Transform::UpdateTransformMatrix(transform);
		glm::vec2 spriteSize = sprite.m_Texture->GetSize();
		glm::vec2 spriteScale = spriteSize.x > spriteSize.y ? spriteSize / spriteSize.x : spriteSize / spriteSize.y;
		auto finalTransformMatrix = glm::scale(transform.m_TransformMatrix, {spriteScale, 1.f});

		position = finalTransformMatrix * glm::vec4(-0.5f, -0.5f, 0.f, 1.f);
		Renderer2D::AppendSingleVertexData(position, tint, { 0.f, 0.f }, sprite.m_TextureTiling, textureIndex);

		position = finalTransformMatrix * glm::vec4(0.5f, -0.5f, 0.f, 1.f);
		Renderer2D::AppendSingleVertexData(position, tint, { 1.f, 0.f }, sprite.m_TextureTiling, textureIndex);

		position = finalTransformMatrix * glm::vec4(0.5f, 0.5f, 0.f, 1.f);
		Renderer2D::AppendSingleVertexData(position, tint, { 1.f, 1.f }, sprite.m_TextureTiling, textureIndex);

		position = finalTransformMatrix * glm::vec4(-0.5f, 0.5f, 0.f, 1.f);
		Renderer2D::AppendSingleVertexData(position, tint, { 0.f, 1.f }, sprite.m_TextureTiling, textureIndex);

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}

	void Renderer2D::DrawSubQuad(TransformComponent& transform, SubSpriteComponent& subSprite, const glm::vec4& tint)
	{
		/*if (s_Data.QuadIndexCount >= s_Data.MaxIndices)
			FlushAndReset();

		float textureIndex = 0.f;
		for (size_t i = 0; i < s_Data.TextureSlotIndex; i++)
		{
			if (s_Data.Textures[i]->GetID() == subSprite.m_AtlasTexture->GetID())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.f)
		{
			textureIndex = (float)s_Data.TextureSlotIndex;

			s_Data.Textures[s_Data.TextureSlotIndex] = subSprite.m_AtlasTexture;
			s_Data.TextureSlotIndex++;
		}

		glm::vec3 position;

		Transform::UpdateTransformMatrix(transform);

		position = transform.m_TransformMatrix * glm::vec4(-0.5f, -0.5f, 0.f, 1.f);
		Renderer2D::AppendSingleVertexData(position, tint, subSprite.m_TexCoords[0], { 1.f, 1.f }, textureIndex);

		position = transform.m_TransformMatrix * glm::vec4(0.5f, -0.5f, 0.f, 1.f);
		Renderer2D::AppendSingleVertexData(position, tint, subSprite.m_TexCoords[1], { 1.f, 1.f }, textureIndex);

		position = transform.m_TransformMatrix * glm::vec4(0.5f, 0.5f, 0.f, 1.f);
		Renderer2D::AppendSingleVertexData(position, tint, subSprite.m_TexCoords[2], { 1.f, 1.f }, textureIndex);

		position = transform.m_TransformMatrix * glm::vec4(-0.5f, 0.5f, 0.f, 1.f);
		Renderer2D::AppendSingleVertexData(position, tint, subSprite.m_TexCoords[3], { 1.f, 1.f }, textureIndex);

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;*/
	}

	/*void Renderer2D::DrawFromTileMap(TileMapComponent& tileMap, const glm::vec4& tint)
	{
		const uint32_t mapHeight = tileMap.m_TileMap->length() / tileMap.m_MapWidth;
		for (size_t y = 0; y < mapHeight; y++)
		{
			for (size_t x = 0; x < tileMap.m_MapWidth; x++)
			{
				const char tileCode = tileMap.m_TileMap->at(x + y * tileMap.m_MapWidth);

				TransformComponent transform = TransformComponent();
				Transform::SetPosition(transform, { x, mapHeight - y, 0.f });

				if (tileMap.m_TileDictionary->find(tileCode) != tileMap.m_TileDictionary->end())
				{
					glm::vec2 scale = tileMap.m_TileDictionary->at(tileCode)->m_TexSize;
					Transform::SetScale(transform, { scale.x, scale.y, 1.f });
					//DrawSubQuad(transform, tileMap.m_TileDictionary->at(tileCode), tint);
				}
			}
		}
	}*/

	void Renderer2D::ResetStats()
	{
		memset(&s_Data.Stats, 0, sizeof(Statistics));
	}
	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_Data.Stats;
	}
}
