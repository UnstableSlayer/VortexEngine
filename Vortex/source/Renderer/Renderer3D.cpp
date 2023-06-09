#include "vpch.h"
#include "Renderer3D.h"

#include "Core/App.h"
#include "Environment/ComponentModifiers.h"
#include "Renderer/RenderCommand.h"

namespace Vortex 
{
	struct Renderer3DData
	{
		Ref<Framebuffer> RendererFB;
		Ref<Shader> PostEffectsShader;
		Ref<VertexArray> RendererFBQuad;

		glm::vec3* CameraPos;
		glm::mat4 ViewProjMatrix;
	};
	static Renderer3DData s_Data;

	void Renderer3D::Init()
	{
		//Renderer framebuffer and renderer quad init
		{
			FramebufferParams fbParams;
			fbParams.Width = App::Get().GetWindow().GetWindowWidth() / App::Get().GetWindow().GetPixelWidth();
			fbParams.Height = App::Get().GetWindow().GetWindowHeight() / App::Get().GetWindow().GetPixelHeight();

			s_Data.RendererFB = Framebuffer::Create(fbParams);
			s_Data.RendererFBQuad = VertexArray::Create();

			float* vertices = new float[] {
					-1.f, -1.f, 0.f,	0.f, 0.f,
					 1.f, -1.f, 0.f,	1.f, 0.f,
					 1.f,  1.f, 0.f,	1.f, 1.f,
					-1.f,  1.f, 0.f,	0.f, 1.f 
			};
			Ref<VertexBuffer> fbVbo = VertexBuffer::Create(vertices, sizeof(vertices) * 5 * 4);
			fbVbo->SetLayout({
				{ ShaderDataType::Vec3f, "aPos" },
				{ ShaderDataType::Vec2f, "aTexCoord"}
				});
			s_Data.RendererFBQuad->AddVertexBuffer(fbVbo);
			delete[] vertices;

			uint32_t* indices = new uint32_t[]{
				0, 1, 2,	// 0 2 3
				2, 3, 0		// 3 1 0
			};

			Ref<IndexBuffer> fbIbo = IndexBuffer::Create(indices, 6);
			s_Data.RendererFBQuad->SetIndexBuffer(fbIbo);
			delete[] indices;

			s_Data.PostEffectsShader = Shader::Create("Shaders/PostEffectShader.glsl");
			s_Data.PostEffectsShader->Bind();
			s_Data.PostEffectsShader->SetUniformInt("uTexture", 0);
		}
	}

	void Renderer3D::Destroy()
	{
	}

	void Renderer3D::BeginScene(CameraComponent& camera, TransformComponent& transform)
	{
		Transform::UpdateTransformMatrix(transform);
		Camera::RecalculateViewMatrix(camera, transform);

		s_Data.CameraPos = &transform.m_Position;

		s_Data.RendererFB->Bind();

		s_Data.ViewProjMatrix = camera.m_ViewProjectionMatrix;
	}

	void Renderer3D::EndScene()
	{
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

	void Renderer3D::EndSceneAndRenderToFramebuffer(Ref<Framebuffer>& targetFB)
	{
		
	}

	Ref<Framebuffer>& Renderer3D::GetRendererFramebuffer() { return s_Data.RendererFB; }

	void Renderer3D::DrawMesh(TransformComponent& transform, StaticMeshComponent& staticMesh)
	{
		Transform::UpdateTransformMatrix(transform);

		//if (IsOutsideOfViewport(transform))
		//	return;

		staticMesh.material.m_Shader->Bind();
		staticMesh.material.m_Shader->SetUniformMat4("uViewProj", s_Data.ViewProjMatrix);
		staticMesh.material.m_Shader->SetUniformMat4("uTransformMatrix", transform.m_TransformMatrix);
		
		for (size_t i = 0; i < staticMesh.mesh.m_Count; i++)
		{
			staticMesh.material.m_Texture->Bind();
			staticMesh.mesh.m_Data[i]->Bind();
			RenderCommand::DrawIndexed(staticMesh.mesh.m_Data[i]);
		}
	}

	bool Renderer3D::IsOutsideOfViewport(TransformComponent& transform)
	{
		return false;
	}
}