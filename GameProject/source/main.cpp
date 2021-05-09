#include <string>
#include <functional>
#include <sstream>

#include <VortexEngine.h>
#include <chrono>

class ExampleLayer : public Vortex::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override
	{
		//VORTEX_APP_INFO("ExampleLayer::Update");
	}

	void OnEvent(Vortex::Event& event) override
	{
		//VORTEX_APP_TRACE("{0}", event.ToString());
	}

	virtual void OnImGuiRender() override
	{
		//ImGui::Begin("Hello");
		//ImGui::Text("Hello World!");
		//ImGui::End();
	}
};

class GameApplication : public Vortex::ApplicationClass
{
public :
	GameApplication()
	{
		m_Camera = Vortex::OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);

		m_Window = std::unique_ptr<Vortex::Window>(Vortex::Window::Create(Vortex::WindowProperties("Vortex Engine Example Window", 1366, 768)));
		m_Window->SetEventCallback(VORTEX_BIND_EVENT(ApplicationClass::OnEvent));

		PushLayer(new ExampleLayer());

		m_ImGuiLayer = new Vortex::ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(Vortex::VertexArray::Create());

		float verticies[(3 + 4) * 4] =
		{
			-0.5f,  -0.5f,  0.5f,	1.0f, 0.0f, 0.0f, 1.0f, // Front Left		0
			 0.5f,  -0.5f,  0.5f,	0.6f, 0.4f, 0.8f, 1.0f, // Front Right	1
			 0.0f,   0.5f,  0.0f,	0.2f, 0.8f, 0.5f, 1.0f, // Top			2
			 0.0f,  -0.5f,  -0.5f,	1.0f, 0.0f, 0.0f, 1.0f // Back Middle	3
		};

		std::shared_ptr<Vortex::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Vortex::VertexBuffer::Create(verticies, sizeof(verticies)));

		vertexBuffer->SetLayout(
			{
				{ Vortex::ShaderDataType::Vec3f, "aPos" },
				{ Vortex::ShaderDataType::Vec4f, "aColor" }
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3 * 4] = {
			0, 1, 2,
			1, 3, 2,
			0, 3, 2,
			3, 1, 0
		};

		std::shared_ptr<Vortex::IndexBuffer> indexBuffer;
		indexBuffer.reset(Vortex::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_Shader.reset(Vortex::Shader::Create("D:\\Dev\\source\\repos\\VortexEngine\\Shaders\\vertex.txt", "D:\\Dev\\source\\repos\\VortexEngine\\Shaders\\fragment.txt"));
	}

	~GameApplication()
	{
		
	}

	virtual void OnStart() override
	{
		glm::vec3 position = glm::vec3(0.f);
		glm::vec3 rotation = glm::vec3(0.f);
		m_Window->SetVSync(true);
		VORTEX_CORE_CRITICAL("VSync: {0}", m_Window->IsVSync());

		while (m_Running)
		{
			Vortex::RenderCommand::Clear({ 0.1f, 0.1f, 0.1f, 1.f });

			Vortex::Renderer::BeginScene(m_Camera);

			if (Vortex::Input::IsKeyPressed(Vortex::Key::W)) position.z += 0.05f;
			if (Vortex::Input::IsKeyPressed(Vortex::Key::S)) position.z -= 0.05f;
			if (Vortex::Input::IsKeyPressed(Vortex::Key::A)) position.x -= 0.05f;
			if (Vortex::Input::IsKeyPressed(Vortex::Key::D)) position.x += 0.05f;
			if (Vortex::Input::IsKeyPressed(Vortex::Key::Q)) position.y -= 0.05f;
			if (Vortex::Input::IsKeyPressed(Vortex::Key::E)) position.y += 0.05f;

			rotation = glm::vec3(Vortex::Input::GetMouseY(), -Vortex::Input::GetMouseX(), 0.f);

			//rotation.y += 0.01f;
			m_Camera.SetPosition(position);// * glm::normalize(rotation));
			m_Camera.SetRotation(rotation);

			m_Shader->Bind();
			m_Shader->SetUniformMat4("u_viewProj", m_Camera.GetViewProjectionMatrix());

			Vortex::Renderer::Submit(m_VertexArray);

			Vortex::Renderer::EndScene();

			for (Vortex::Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Vortex::Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}
};


Vortex::ApplicationClass* Vortex::CreateApplication()
{
	VORTEX_CORE_INFO("Initializating Engine Logger...OK");
	VORTEX_APP_INFO("Initializating Application Logger...OK");

	return new GameApplication();
}

