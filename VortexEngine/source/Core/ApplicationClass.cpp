#include "vpch.h"

#include "ApplicationClass.h"

#include "Core/Input.h"
#include "Core/Logger.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Vortex
{
	ApplicationClass* ApplicationClass::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Int:			return GL_INT;
		case ShaderDataType::Vec2i:			return GL_INT;
		case ShaderDataType::Vec3i:			return GL_INT;
		case ShaderDataType::Vec4i:			return GL_INT;
		case ShaderDataType::Float:			return GL_FLOAT;
		case ShaderDataType::Vec2f:			return GL_FLOAT;
		case ShaderDataType::Vec3f:			return GL_FLOAT;
		case ShaderDataType::Vec4f:			return GL_FLOAT;
		case ShaderDataType::Mat3:			return GL_FLOAT;
		case ShaderDataType::Mat4:			return GL_FLOAT;
		case ShaderDataType::Bool:			return GL_BOOL;
		}
	}

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
			glClearColor(0.0f, 0.0f, 0.1f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			m_VertexArray->Bind();

			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			GLenum result = glGetError();
			switch (result)
			{
				case GL_INVALID_ENUM:						VORTEX_CORE_ERROR("INVALID ENUM - ({0})", result);						break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:		VORTEX_CORE_ERROR("INVALID FRAMEBUFFER OPERATION - ({0})", result);		break;
				case GL_INVALID_OPERATION:					VORTEX_CORE_ERROR("INVALID OPERATION - ({0})", result);					break;
				case GL_INVALID_INDEX:						VORTEX_CORE_ERROR("INVALID INDEX - ({0})", result);						break;
				case GL_INVALID_VALUE:						VORTEX_CORE_ERROR("INVALID VALUE - ({0})", result);						break;
			}


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