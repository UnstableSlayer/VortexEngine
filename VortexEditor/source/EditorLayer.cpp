#include "EditorLayer.h"

EditorLayer::EditorLayer()
	: Layer("Example")
{
	Vortex::FramebufferParams viewportParams;
	viewportParams.Width = 640;
	viewportParams.Height = 360;
	m_ViewportFB = Vortex::Framebuffer::Create(viewportParams);

	m_Camera = Vortex::SCENE->CreateObject();
	m_Camera.AddComponent<Vortex::TransformComponent>();
	auto& camera = m_Camera.AddComponent<Vortex::CameraComponent>();
	Vortex::Camera::Init(camera, Vortex::CameraType::Perspective, 640, 360);
}

void EditorLayer::Input()
{
    auto& transform = m_Camera.GetComponent<Vortex::TransformComponent>();
    auto& camera = m_Camera.GetComponent<Vortex::CameraComponent>();

    glm::vec3 velocity = glm::vec3(0.f);
    glm::vec3 angularVelocity = glm::vec3(0.f);
    float scale = camera.m_Zoom;

    if (Vortex::Input::IsKeyPressed(Vortex::Key::I)) scale += 10.f * Vortex::Time::GetDeltaTime();
    if (Vortex::Input::IsKeyPressed(Vortex::Key::O)) scale -= 10.f * Vortex::Time::GetDeltaTime();

    if (Vortex::Input::IsKeyPressed(Vortex::Key::S)) velocity.z = 10.f * Vortex::Time::GetDeltaTime();
    if (Vortex::Input::IsKeyPressed(Vortex::Key::W)) velocity.z = -10.f * Vortex::Time::GetDeltaTime();
    if (Vortex::Input::IsKeyPressed(Vortex::Key::A)) velocity.x = -20.f * Vortex::Time::GetDeltaTime();
    if (Vortex::Input::IsKeyPressed(Vortex::Key::D)) velocity.x = 20.f * Vortex::Time::GetDeltaTime();
    if (Vortex::Input::IsKeyPressed(Vortex::Key::Q)) velocity.y = -10.f * Vortex::Time::GetDeltaTime();
    if (Vortex::Input::IsKeyPressed(Vortex::Key::E)) velocity.y = 10.f * Vortex::Time::GetDeltaTime();

    if (Vortex::Input::IsKeyPressed(Vortex::Key::ESC)) Vortex::App::Get().GetWindow().LockCursor(false);
    if (Vortex::Input::IsMouseButtonPressed(Vortex::MouseKey::L)) Vortex::App::Get().GetWindow().LockCursor(true);

    {
        auto [mouseDeltaX, mouseDeltaY] = Vortex::Input::GetMouseDelta();
        {
            float deltaX = mouseDeltaY;
            float deltaY = mouseDeltaX;

            angularVelocity.x = -deltaX / 10.f;
            angularVelocity.y = -deltaY / 10.f;
        }
    }

    Vortex::Transform::Move(transform, transform.m_Rotation * velocity);
    Vortex::Transform::Rotate(transform, glm::normalize(transform.m_Rotation) * angularVelocity);
    Vortex::Camera::PerspectiveZoom(camera, scale);
}

void EditorLayer::OnUpdate()
{
	Input();
	auto& transform = m_Camera.GetComponent<Vortex::TransformComponent>();
	auto& camera = m_Camera.GetComponent<Vortex::CameraComponent>();
	Vortex::Renderer2D::BeginScene(camera, transform);
	Vortex::RenderCommand::Clear();

	Vortex::TransformComponent tr;
	Vortex::Transform::SetPosition(tr, { 0, -20, 20 });
	Vortex::Renderer2D::DrawQuad(tr, { 1.0, 0.0, 0.0, 1.0 });

	Vortex::Renderer2D::EndSceneAndRenderToFramebuffer(m_ViewportFB);
}

void EditorLayer::OnImGuiRender()
{
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

				if (ImGui::MenuItem("Exit")) Vortex::App::Get().OnClose();
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

			ImGui::End();
		}

		//Viewport
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));

			ImGui::Begin("Viewport");
			ImVec2 viewportSize = ImGui::GetContentRegionAvail();
			glm::vec2 viewportFbSize = { m_ViewportFB->GetParams().Width, m_ViewportFB->GetParams().Height };

			if (viewportFbSize != *(glm::vec2*)&viewportSize)
			{
				viewportFbSize = { viewportSize.x, viewportSize.y };
				m_ViewportFB->Resize(viewportFbSize);

				//Hack for now
				Vortex::Camera::PerspectiveResize(m_Camera.GetComponent<Vortex::CameraComponent>(), viewportFbSize.x, viewportFbSize.y);
			}

			ImGui::Image((void*)m_ViewportFB->GetColorAttachmentID(), { (float)m_ViewportFB->GetParams().Width, (float)m_ViewportFB->GetParams().Height }, { 0.f, 1.f }, { 1.f, 0.f });

			ImGui::PopStyleVar();
			ImGui::End();
		}

		{
			ImGui::Begin("Hierarchy");
			for (size_t i = 0; i < m_Scene.size(); i++)
			{
				Vortex::Object* object = m_Scene[i];

				const char* name = object->HasComponent<Vortex::TagComponent>() ? object->GetComponent<Vortex::TagComponent>().m_Tag : "Object{" + i + '}';

				if (ImGui::CollapsingHeader(name))
				{
					ImGui::BeginGroup();
					if (object->HasComponent<Vortex::TransformComponent>())// && ImGui::CollapsingHeader("Transform"))
					{
						ImGui::Text("Transform");
						Vortex::TransformComponent& transform = object->GetComponent<Vortex::TransformComponent>();

						glm::vec3 position = transform.m_Position;
						ImGui::InputFloat3("Position", (float*)&position);
						Vortex::Transform::SetPosition(transform, position);

						glm::vec3 rotation = glm::vec3(1.f) * transform.m_Rotation;
						ImGui::InputFloat3("Rotation", (float*)&rotation);
						Vortex::Transform::SetRotation(transform, rotation);

						glm::vec3 scale = transform.m_Scale;
						ImGui::InputFloat3("Scale", (float*)&scale);
						Vortex::Transform::SetScale(transform, scale);
					}
					if (object->HasComponent<Vortex::SpriteComponent>())
					{
						ImGui::Text("Sprite");
						Vortex::SpriteComponent& sprite = object->GetComponent<Vortex::SpriteComponent>();

						glm::vec4 color = sprite.m_Tint;
						ImGui::ColorEdit4("Color", (float*)&color);
						sprite.m_Tint = color;

						static bool state = false;

						if (ImGui::ImageButton((void*)sprite.m_Texture->GetID(), { 128.f, 128.f }, { 0.f, 1.f }, { 1.f, 0.f }))
							state = state ? false : true;

						if (state)
						{
							static bool texturePathTextBoxOpen = false;
							static char path[255];

							if (!texturePathTextBoxOpen)
								strcpy(path, sprite.m_Texture->GetPath());

							texturePathTextBoxOpen = true;

							ImGui::Begin("Select Texture:");
							ImGui::InputText("Path", path, 255);

							if (ImGui::Button("Open"))
							{
								sprite.m_Texture = Vortex::Texture2D::Create(path);
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

void EditorLayer::OnEvent(Vortex::Event& event)
{
	Vortex::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Vortex::WindowResizeEvent>(VORTEX_BIND_EVENT(EditorLayer::OnCameraResize));
}

bool EditorLayer::OnCameraResize(Vortex::WindowResizeEvent& event)
{
	Vortex::Camera::OnWindowResize(event, m_Camera.GetComponent<Vortex::CameraComponent>());
	VORTEX_APP_INFO("Window resized to {0}x{1}", event.GetWidth(), event.GetHeight());
	return false;
}

