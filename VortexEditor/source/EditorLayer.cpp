#include "EditorLayer.h"
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

#define TILEMAP_TEST
//#define SHIP_TEST

namespace Vortex
{
	EditorLayer::EditorLayer()
		: Layer("EditorLayer")
	{
		//Camera
		{
			m_Camera = m_Scene.CreateObject();
			auto& transform = m_Camera.AddComponent<Vortex::TransformComponent>();
			auto& camera = m_Camera.AddComponent<Vortex::CameraController>(Vortex::CameraType::Perspective, 16.f, 9.f, 0.1f, 1000.f, 55.f);
			Transform::SetPosition(transform, { 0.f, 0.f, 10.f });
		}

		#ifdef TILEMAP_TEST
        {
            m_TileMap = "31111111111111111119"
                        "20000000000000000008"
                        "20000000000000000008"
                        "20000000000000000008"
                        "20000000000000000008"
                        "20000440000004400008"
                        "20008  200008  20008"
                        "20008  200008  20008"
                        "20008  200008  20008"
                        "20008  200008  20008"
                        "20008  200008  20008"
                        "200008  2008  200008"
                        "2000008 644c 2000008"
                        "20000008    20000008"
                        "20000000111100000008"
                        "20000000000000000008"
                        "20000000000000000008"
                        "20000000000000000008"
                        "20000000000000000008"
                        "6444444444444444444c";

            Vortex::Ref<Vortex::Texture2D> atlasTex = Vortex::Texture2D::Create("Assets/Textures/Set_A_Standard_Coast.png");
            atlasTex->MakeHandleResident();

            m_TextureMap.insert({ '0', Vortex::SubTexture2D::CreateFromPos(atlasTex, { 1, 14 }, { 16, 16 }) });
            m_TextureMap.insert({ '1', Vortex::SubTexture2D::CreateFromPos(atlasTex, { 1, 15 }, { 16, 16 }) });
            m_TextureMap.insert({ '3', Vortex::SubTexture2D::CreateFromPos(atlasTex, { 0, 15 }, { 16, 16 }) });
            m_TextureMap.insert({ '2', Vortex::SubTexture2D::CreateFromPos(atlasTex, { 0, 14 }, { 16, 16 }) });
            m_TextureMap.insert({ '6', Vortex::SubTexture2D::CreateFromPos(atlasTex, { 0, 13 }, { 16, 16 }) });
            m_TextureMap.insert({ '4', Vortex::SubTexture2D::CreateFromPos(atlasTex, { 1, 13 }, { 16, 16 }) });
            m_TextureMap.insert({ 'c', Vortex::SubTexture2D::CreateFromPos(atlasTex, { 2, 13 }, { 16, 16 }) });
            m_TextureMap.insert({ '8', Vortex::SubTexture2D::CreateFromPos(atlasTex, { 2, 14 }, { 16, 16 }) });
            m_TextureMap.insert({ '9', Vortex::SubTexture2D::CreateFromPos(atlasTex, { 2, 15 }, { 16, 16 }) });
        }
        #endif

        #ifdef SHIP_TEST
        {
            using namespace Vortex;

            m_ShipMesh = Vortex::MakeRef<Vortex::Mesh>();
            m_ShipMesh->Load("Assets/Models/Ship0.fbx");

            m_ShipVao = m_ShipMesh->m_Data;

            m_ShipTexture = Vortex::Texture2D::Create("Assets/Textures/Ship0.png",   Vortex::TextureFormat::RGBA16, Vortex::TextureWrap::REPEAT);
            m_ShipTexture->MakeHandleResident();

            m_ShipShader = Vortex::Shader::Create("Shaders/litShaderBindless.glsl");

            m_ShipShader->Bind();
            m_ShipShader->SetUniformTexHandle("uTexture", m_ShipTexture->GetBindlessHandle());
        }

        //VORTEX_APP_INFO("DeltaTime: {0}", Vortex::Time::GetDeltaTime());
        #endif

		Vortex::FramebufferParams params;
		params.Width = Vortex::ApplicationClass::Get().GetWindow().GetWindowWidth();
		params.Height = Vortex::ApplicationClass::Get().GetWindow().GetWindowHeight();
		m_ViewportFramebuffer = Vortex::Framebuffer::Create(params);
	}

	void EditorLayer::Input()
	{
		auto& transform = m_Camera.GetComponent<Vortex::TransformComponent>();
		auto& cameraController = m_Camera.GetComponent<Vortex::CameraController>();

		glm::vec3 velocity = glm::vec3(0.f);
		glm::vec3 angularVelocity = glm::vec3(0.f);
		float scale = cameraController.m_Camera.m_Zoom;

		if (Vortex::Input::IsKeyPressed(Vortex::Key::I)) scale += 10.f * Vortex::Time::GetDeltaTime();
		if (Vortex::Input::IsKeyPressed(Vortex::Key::O)) scale -= 10.f * Vortex::Time::GetDeltaTime();

		if (Vortex::Input::IsKeyPressed(Vortex::Key::S)) velocity.z += 40.f * Vortex::Time::GetDeltaTime();
		if (Vortex::Input::IsKeyPressed(Vortex::Key::W)) velocity.z -= 40.f * Vortex::Time::GetDeltaTime();
		if (Vortex::Input::IsKeyPressed(Vortex::Key::A)) velocity.x = -60.f * Vortex::Time::GetDeltaTime();
		if (Vortex::Input::IsKeyPressed(Vortex::Key::D)) velocity.x = 60.f * Vortex::Time::GetDeltaTime();
		if (Vortex::Input::IsKeyPressed(Vortex::Key::Q)) velocity.y = -40.f * Vortex::Time::GetDeltaTime();
		if (Vortex::Input::IsKeyPressed(Vortex::Key::E)) velocity.y = 40.f * Vortex::Time::GetDeltaTime();

		if (Vortex::Input::IsMouseButtonPressed(Vortex::Mouse::R))
		{
			Vortex::ApplicationClass::Get().GetWindow().LockCursor(true);
			auto [mousePosX, mousePosY] = Vortex::Input::GetMouseDelta();
			{
				float deltaX = mousePosY;
				float deltaY = mousePosX;

				angularVelocity.x = deltaX * 0.1f;// * Vortex::Time::GetDeltaTime();
				angularVelocity.y = deltaY * 0.1f;// * Vortex::Time::GetDeltaTime();
			}
		}
		else
			Vortex::ApplicationClass::Get().GetWindow().LockCursor(false);

		glm::vec3 forward = glm::vec3(0.f, 0.f, 1.f) * transform.m_Rotation;
		glm::vec3 up = glm::vec3(0.f, 1.f, 0.f) * transform.m_Rotation;
		glm::vec3 right = glm::vec3(1.f, 0.f, 0.f) * transform.m_Rotation;

		Transform::Move(transform, velocity.x * right + velocity.y * up + velocity.z * forward);
		Transform::Rotate(transform, angularVelocity);

        //Hack for now
		Camera::PerspectiveZoom(cameraController.m_Camera, scale);
	}

	void EditorLayer::OnUpdate()
	{
		Input();

        RenderCommand::Clear();
        #ifndef SHIP_TEST
		Vortex::Renderer2D::BeginScene(m_Camera);
        Vortex::RenderCommand::Clear();
        #ifdef TILEMAP_TEST
		Vortex::Renderer2D::DrawFromTileMap(m_TileMap, 20, m_TextureMap, m_Color);
        #endif

        Vortex::Renderer2D::EndSceneAndRenderToFramebuffer(m_ViewportFramebuffer);
        #endif

        #ifdef SHIP_TEST
        auto& camera = m_Camera.GetComponent<Vortex::CameraComponent>();
        auto& cameraTransform = m_Camera.GetComponent<Vortex::TransformComponent>();

        m_ShipShader->Bind();
        m_ShipShader->SetUniformMat4("uViewProj", camera.GetViewProjectionMatrix(cameraTransform.m_Position, cameraTransform.m_Rotation));

        //m_ShipTexture->Bind(1);
        m_ShipVao->Bind();
        Vortex::RenderCommand::DrawIndexed(m_ShipVao, m_ShipVao->GetIndexBuffer()->GetCount());
        #endif
	}

	void EditorLayer::OnEvent(Vortex::Event& event)
	{
		m_Camera.GetComponent<CameraController>().OnEvent(event);
	}

	void EditorLayer::OnImGuiRender()
	{
		// Note: Switch this to true to enable dockspace
		static bool dockingEnabled = true;
		if (dockingEnabled)
		{
			static bool dockspaceOpen = true;
			static bool opt_fullscreen_persistant = true;
			bool opt_fullscreen = opt_fullscreen_persistant;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
			// because it would be confusing to have two docking targets within each others.
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->Pos);
				ImGui::SetNextWindowSize(viewport->Size);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}

			// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
			// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
			// all active windows docked into it will lose their parent and become undocked.
			// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
			// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
			ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			// DockSpace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					// Disabling fullscreen would allow the window to be moved to the front of other windows, 
					// which we can't undo at the moment without finer window depth/z control.
					//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

					if (ImGui::MenuItem("Exit")) Vortex::ApplicationClass::Get().OnClose();
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

			//bool viewportFocused = ImGui::IsWindowFocused();
            //bool viewportHovered = ImGui::IsWindowHovered();
            //ApplicationClass::Get().GetImGuiLayer()->BlockEvents(!viewportFocused && !viewportHovered);

			//Stats
			{
				ImGui::Begin("Stats");

				ImGui::Text("DeltaTime: %f", Vortex::Time::GetDeltaTime() * 1000.f);

				auto stats = Vortex::Renderer2D::GetStats();
				ImGui::Text("Draw Calls: %d", stats.DrawCalls);
				ImGui::Text("Quad Count: %d", stats.QuadCount);
				ImGui::Text("Vertex Count: %d", stats.GetVertexCount());
				ImGui::Text("Index Count: %d", stats.GetIndexCount());

                glm::vec4 color = m_Color;
                ImGui::ColorEdit4("Color", (float*)&color);
                m_Color = color;

				ImGui::End();
			}
			
			//Viewport
 			{
 				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));

 				ImGui::Begin("Viewport");
 				ImVec2 viewportSize = ImGui::GetContentRegionAvail();
 				glm::vec2 viewportFbSize = {m_ViewportFramebuffer->GetParams().Width, m_ViewportFramebuffer->GetParams().Height};

 				if (viewportFbSize != *(glm::vec2*)&viewportSize)
 				{
 					viewportFbSize = { viewportSize.x, viewportSize.y };
					m_ViewportFramebuffer->Resize(viewportFbSize);

                    //Hack for now
					Camera::PerspectiveResize(m_Camera.GetComponent<CameraController>().m_Camera, viewportFbSize.x, viewportFbSize.y);
				}

				ImGui::Image((void*)m_ViewportFramebuffer->GetColorAttachmentID(), { (float)m_ViewportFramebuffer->GetParams().Width, (float)m_ViewportFramebuffer->GetParams().Height }, { 0.f, 1.f }, { 1.f, 0.f });

				ImGui::PopStyleVar();
				ImGui::End();
			}

			{
				ImGui::Begin("Hierarchy");
				for (size_t i = 0; i < m_Scene.size(); i++)
				{
					Object* object = m_Scene[i];

					const char* name = object->HasComponent<TagComponent>() ? object->GetComponent<TagComponent>().m_Tag : "Object{" + i + '}';

					if (ImGui::CollapsingHeader(name))
					{
						ImGui::BeginGroup();
						if (object->HasComponent<TransformComponent>())// && ImGui::CollapsingHeader("Transform"))
						{
							ImGui::Text("Transform");
							TransformComponent& transform = object->GetComponent<TransformComponent>();

							glm::vec3 position = transform.m_Position;
							ImGui::InputFloat3("Position", (float*)&position);
							Transform::SetPosition(transform, position);

							glm::vec3 rotation = glm::vec3(1.f) * transform.m_Rotation;
							ImGui::InputFloat3("Rotation", (float*)&rotation);
							Transform::SetRotation(transform, rotation);

							glm::vec3 scale = transform.m_Scale;
							ImGui::InputFloat3("Scale", (float*)&scale);
							Transform::SetScale(transform, scale);
						}
						if (object->HasComponent<SpriteComponent>())
						{
							ImGui::Text("Sprite");
							SpriteComponent& sprite = object->GetComponent<SpriteComponent>();

							glm::vec4 color = sprite.m_Tint;
							ImGui::ColorEdit4("Color", (float*)&color);
							sprite.m_Tint = color;

							static bool state = false;

							if(ImGui::ImageButton((void*)sprite.m_Texture->GetID(), { 128.f, 128.f }, { 0.f, 1.f }, { 1.f, 0.f }))
								state = state ? false : true;

							if (state)
							{
								static bool texturePathTextBoxOpen = false;
								static char path[255];

								if(!texturePathTextBoxOpen)
									strcpy(path, sprite.m_Texture->GetPath());

								texturePathTextBoxOpen = true;

								ImGui::Begin("Select Texture:");
								ImGui::InputText("Path", path, 255);

								if (ImGui::Button("Open"))
								{
									sprite.m_Texture = Texture2D::Create(path);
									state = false;

									texturePathTextBoxOpen = false;
								}

								ImGui::End();
							}

						}
						ImGui::EndGroup();
					}
				}
				ImGui::End();
			}
			ImGui::End();
		}
	}
}
