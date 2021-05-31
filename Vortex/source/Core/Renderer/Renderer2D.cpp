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
	struct Renderer2DData
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> DefaultShader;
		Ref<Texture> DefaultTexture;
	};

	static Renderer2DData* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DData();
		s_Data->QuadVertexArray = VertexArray::Create();

		float quadVertices[(3 + 2) * 4] = {
			-0.5f, -0.5f,  0.0f,	0.0f, 0.0f,
			 0.5f, -0.5f,  0.0f,	1.0f, 0.0f,
			 0.5f,  0.5f,  0.0f,	1.0f, 1.0f,
			-0.5f,  0.5f,  0.0f,	0.0f, 1.0f
		};

		Ref<VertexBuffer> quadVB = VertexBuffer::Create(quadVertices, sizeof(quadVertices));
		quadVB->SetLayout({
			{ ShaderDataType::Vec3f, "aPos" },
			{ ShaderDataType::Vec2f, "aTexCoord" }
		});
		s_Data->QuadVertexArray->AddVertexBuffer(quadVB);

		uint32_t quadIndices[2 * 3] = {
			0, 1, 2,
			2, 3, 0
		};
		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t));
		s_Data->QuadVertexArray->SetIndexBuffer(quadIB);

		uint32_t textureData = 0xffffffff;
		s_Data->DefaultTexture = Texture2D::Create(1, 1);
		s_Data->DefaultTexture->SetData(&textureData, sizeof(uint32_t));
		s_Data->DefaultTexture->Bind();

		s_Data->DefaultShader = Shader::Create("Shaders/FlatColor.glsl");
		s_Data->DefaultShader->SetUniformInt("uTexture", 0);
		s_Data->DefaultShader->SetUniformVec2("uTextureScale", glm::vec2(1.f));
	}
	void Renderer2D::Destroy()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->DefaultShader->SetUniformMat4("uViewProj", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(TransformComponent& transform, const glm::vec4& color)
	{
		s_Data->DefaultShader->Bind();
		s_Data->DefaultShader->SetUniformMat4("uTransform", transform.GetTransformMatrix());
		s_Data->DefaultShader->SetUniformVec4("uTextureColor", color);

		s_Data->DefaultTexture->Bind();
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
	void Renderer2D::DrawQuad(TransformComponent& transform, const Texture2D& texture, const glm::vec2& textureScale, const glm::vec4& tint)
	{
		const char* functionName = __FUNCTION__;
		Timer timer = Timer("test", [&](ProfileResult profileReport) {VORTEX_CORE_INFO("{0}: {1} ms", functionName, profileReport.Time); });
		
		
		s_Data->DefaultShader->Bind();
		s_Data->DefaultShader->SetUniformMat4("uTransform", transform.GetTransformMatrix());
		s_Data->DefaultShader->SetUniformVec4("uTextureColor", tint);
		s_Data->DefaultShader->SetUniformVec2("uTextureScale", textureScale);

		texture.Bind();
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}
}