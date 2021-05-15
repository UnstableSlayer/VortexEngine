#include <string>
#include <functional>
#include <sstream>
#include <iostream>

#include <VortexEngine.h>
#include <chrono>

class GameApplication : public Vortex::ApplicationClass
{
public:
	GameApplication() : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		m_Camera = Vortex::OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);

		m_Window = std::unique_ptr<Vortex::Window>(Vortex::Window::Create(Vortex::WindowProperties("Vortex Engine Example Window", 1366, 768)));
		m_Window->SetEventCallback(VORTEX_BIND_EVENT(ApplicationClass::OnEvent));
		m_Window->SetVSync(false);

		m_ImGuiLayer = new Vortex::ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(Vortex::VertexArray::Create());

		Vortex::Ref<Vortex::VertexBuffer> vertexBuffer;

		float triangleVerticies[(3 + 2) * 4] =
		{
			-0.5f,  -0.5f,  0.0f,	0.0f, 0.0f,		//-0.5f,  -0.5f,  1.0f,	0.0f, 0.0f, 0.0f, 0.1f, // Bottom Left		0
			 0.5f,  -0.5f,  0.0f,	1.0f, 0.0f,		// 0.5f,  -0.5f,  1.0f,	1.0f, 0.0f, 0.8f, 0.1f, // Bottom Right		1
			 0.5f,   0.5f,  0.0f,	1.0f, 1.0f,		// 0.5f,   0.5f,  1.0f,	1.0f, 1.0f, 0.5f, 0.1f, // Top   Right		2
			-0.5f,   0.5f,  0.0f,	0.0f, 1.0f		//-0.5f,   0.5f,  1.0f,	0.0f, 1.0f, 0.0f, 0.1f  // Top   Left		3
		};

		vertexBuffer.reset(Vortex::VertexBuffer::Create(triangleVerticies, sizeof(triangleVerticies)));
		vertexBuffer->SetLayout(
			{
				{ Vortex::ShaderDataType::Vec3f, "aPos"},
				{ Vortex::ShaderDataType::Vec2f, "aTexCoord"}
			}
		);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		Vortex::Ref<Vortex::IndexBuffer> indexBuffer;
		uint32_t indices[3 * 2] = {
			0, 1, 2,
			0, 3, 2
		};
		indexBuffer.reset(Vortex::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_Shader.reset(Vortex::Shader::Create(".\\Shaders\\textureVertex.txt", ".\\Shaders\\textureFragment.txt"));
		m_Shader->SetUniformInt("u_Texture", 0);

		m_Texture = Vortex::Texture2D::Create(".\\Textures\\testTexture.png");

		Vortex::Object sprite = m_Registry.CreateObject();
		Vortex::TransformComponent& transform = sprite.AddComponent<Vortex::TransformComponent>();
		transform.SetPosition(glm::vec3(0.f, 0.5f, 0.f));

	}

	~GameApplication()
	{
		
	}

	virtual void OnUpdate() override 
	{
		static glm::vec3 position = glm::vec3(0.f);
		static glm::vec3 rotation = glm::vec3(0.f);
		static float scale = 1.f;
		//VORTEX_CORE_CRITICAL("VSync: {0}", m_Window->IsVSync());
		static auto& transform = m_Registry[0]->GetComponent<Vortex::TransformComponent>();

		{
			VORTEX_APP_INFO("DeltaTime: {0}", m_Time->GetDeltaTime() * 1000);
			float scaleSpeed = (transform.m_Scale.x / 2.f) * m_Time->GetDeltaTime();

			if (Vortex::Input::IsKeyPressed(Vortex::Key::S)) scale -= scaleSpeed;
			if (Vortex::Input::IsKeyPressed(Vortex::Key::W)) scale += scaleSpeed;
			if (Vortex::Input::IsKeyPressed(Vortex::Key::A)) position.x -= 2.f * m_Time->GetDeltaTime();
			if (Vortex::Input::IsKeyPressed(Vortex::Key::D)) position.x += 2.f * m_Time->GetDeltaTime();
			if (Vortex::Input::IsKeyPressed(Vortex::Key::Q)) position.y -= 2.f * m_Time->GetDeltaTime();
			if (Vortex::Input::IsKeyPressed(Vortex::Key::E)) position.y += 2.f * m_Time->GetDeltaTime();
			
			if (Vortex::Input::IsKeyPressed(Vortex::Key::Up)) rotation.x += 60.f * m_Time->GetDeltaTime();
			if (Vortex::Input::IsKeyPressed(Vortex::Key::Down)) rotation.x -= 60.f * m_Time->GetDeltaTime();
			if (Vortex::Input::IsKeyPressed(Vortex::Key::Left)) rotation.y += 60.f * m_Time->GetDeltaTime();
			if (Vortex::Input::IsKeyPressed(Vortex::Key::Right)) rotation.y -= 60.f * m_Time->GetDeltaTime();


			Vortex::RenderCommand::Clear({ 0.1f, 0.1f, 0.1f, 1.f });

			Vortex::Renderer::BeginScene(m_Camera);


			m_Texture->Bind(0);
			m_Shader->SetUniformMat4("u_viewProj", m_Camera.GetViewProjectionMatrix());

			transform.SetPosition(position);
			transform.SetRotation(rotation);
			transform.SetScale(glm::vec3(scale));
			Vortex::Renderer::Submit(m_VertexArray, m_Shader, transform.GetTransformMatrix());

			Vortex::Renderer::EndScene();

			m_ImGuiLayer->Begin();
			for (Vortex::Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();
			m_Window->OnUpdate();
		}
	}

	virtual void OnStart() override
	{

	}

private:
	Vortex::Scene m_Registry;

	Vortex::Ref<Vortex::Texture2D> m_Texture;
	Vortex::Ref<Vortex::Texture2D> m_Texture1;

	Vortex::Ref<Vortex::Shader> m_Shader;
	Vortex::Ref<Vortex::VertexArray> m_VertexArray;

	Vortex::OrthographicCamera m_Camera;

	std::vector<Vortex::ProfileResult> m_ProfileResults;
};


Vortex::ApplicationClass* Vortex::CreateApplication()
{
	VORTEX_CORE_INFO("Initializating Engine Logger...OK");
	VORTEX_APP_INFO("Initializating Application Logger...OK");

	return new GameApplication();
}

