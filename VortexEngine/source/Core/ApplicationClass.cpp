#include "vpch.h"

#include "ApplicationClass.h"

#include "Core/Input.h"
#include "Core/Logger.h"

#include "Renderer/Renderer.h"

namespace Vortex
{
	ApplicationClass* ApplicationClass::s_Instance = nullptr;

	ApplicationClass::ApplicationClass()
	{
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(VORTEX_BIND_EVENT(ApplicationClass::OnEvent));
		
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());
	
		float verticies[3 * 6] =
		{
			-0.5f, -0.5f,  0.0f,	1.0f, 0.0f, 0.0f,
			0.5f,  -0.5f,  0.0f,	0.6f, 0.0f, 0.0f,
			0.0f,   0.5f,  0.0f,	0.2f, 0.0f, 0.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(verticies, sizeof(verticies)));

		vertexBuffer->SetLayout(
			{
				{ ShaderDataType::Vec3f, "aPos" },
				{ ShaderDataType::Vec3f, "aColor" } 
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_Shader.reset(Shader::Create("D:\\Dev\\source\\repos\\VortexEngine\\Shaders\\vertex.txt", "D:\\Dev\\source\\repos\\VortexEngine\\Shaders\\fragment.txt"));
	}

	ApplicationClass::~ApplicationClass()
	{

	}

	void ApplicationClass::OnStart()
	{
		while (m_Running)
		{
			RenderCommand::Clear({0.5f, 0.2f, 0.1f, 1.f});

			Renderer::BeginScene();

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void ApplicationClass::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(VORTEX_BIND_EVENT(ApplicationClass::OnWindowClose));

		for (auto i = m_LayerStack.end(); i != m_LayerStack.begin();)
		{
			(*--i)->OnEvent(event);

			if (event.m_Handled)
				break;
		}
	}

	void ApplicationClass::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void ApplicationClass::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	bool ApplicationClass::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}
}