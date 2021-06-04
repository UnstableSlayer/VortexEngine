#include "ExampleLayer.h"
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

//#define BENCH

std::unordered_map<char, Vortex::Ref<Vortex::SubTexture2D>> m_TextureMap;
const char* m_TileMap = "0000111110000"
						"0001002001000"
						"0001003001000"
						"0001002001000"
						"0001003001000"
						"0001002001000"
						"0001003001000"
						"0001002001000"
						"0001003001000"
						"0001002001000"
						"0001003001000"
						"0001002001000"
						"0001003001000"
						"0001002001000"
						"0001003001000"
						"0001002001000"
						"0001003001000"
						"0001002001000"
						"0001003001000"
						"0001002001000"
						"0000111110000";

ExampleLayer::ExampleLayer()
	: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
	transformComp.reset(new Vortex::TransformComponent());

#ifndef BENCH
	//Doom Wall
	{
		Vortex::Object obj = m_Scene.CreateObject();
		obj.AddComponent<Vortex::TagComponent>("DW");
		obj.AddComponent<Vortex::TransformComponent>();

		auto& renderer2DComponent = obj.AddComponent<Vortex::SubSpriteComponent>();
		renderer2DComponent.m_Sprite = Vortex::SubTexture2D::CreateFromPos(Vortex::Texture2D::Create("Textures/testAtlas.png"), { 0, 1 }, { 16, 16 });
	}

	//Skull
	{
		Vortex::Object obj = m_Scene.CreateObject();
		obj.AddComponent<Vortex::TagComponent>("SK");

		auto& transform = obj.AddComponent<Vortex::TransformComponent>();
		transform.SetPosition({ 1.f, -2.f, 0.f });
		
		auto& renderer2DComponent = obj.AddComponent<Vortex::SubSpriteComponent>();
		renderer2DComponent.m_Sprite = Vortex::SubTexture2D::CreateFromPos(Vortex::Texture2D::Create("Textures/testAtlas.png"), { 1, 1 }, { 16, 16 });
	}

	//Spiderman
	{
		Vortex::Object obj = m_Scene.CreateObject();
		obj.AddComponent<Vortex::TagComponent>("SM");

		auto& transform = obj.AddComponent<Vortex::TransformComponent>();
		transform.SetPosition({ -2.f, 1.f, 0.f });

		auto& renderer2DComponent = obj.AddComponent<Vortex::SubSpriteComponent>();
		renderer2DComponent.m_Sprite = Vortex::SubTexture2D::CreateFromPos(Vortex::Texture2D::Create("Textures/testAtlas.png"), { 1, 0 }, { 16, 16 });
	}


	//Background Grid
	{
		Vortex::Object obj = m_Scene.CreateObject();
		obj.AddComponent<Vortex::TagComponent>("bg0");

		obj.AddComponent<Vortex::TransformComponent>().SetScale(glm::vec3(40.f));

		auto& renderer2DComponent = obj.AddComponent<Vortex::SpriteComponent>();
		renderer2DComponent.m_Sprite = Vortex::Texture2D::Create("Textures/bg0.png");
		renderer2DComponent.m_TextureTiling = glm::vec2(20.f);
		renderer2DComponent.m_Tint = { 1.f, 1.f, 1.f, 0.2f };
	}

	m_TextureMap.insert({ '0', Vortex::SubTexture2D::CreateFromPos(Vortex::Texture2D::Create("Textures/testAtlas.png"), { 0, 0 }, { 16, 16 }) });
	m_TextureMap.insert({ '1', Vortex::SubTexture2D::CreateFromPos(Vortex::Texture2D::Create("Textures/testAtlas.png"), { 0, 1 }, { 16, 16 }) });
	m_TextureMap.insert({ '2', Vortex::SubTexture2D::CreateFromPos(Vortex::Texture2D::Create("Textures/testAtlas.png"), { 1, 0 }, { 16, 16 }) });
	m_TextureMap.insert({ '3', Vortex::SubTexture2D::CreateFromPos(Vortex::Texture2D::Create("Textures/testAtlas.png"), { 1, 1 }, { 16, 16 }) });
#endif

#ifdef BENCH
	Vortex::Ref<Vortex::Texture2D> spiderman = Vortex::Texture2D::Create("Textures/testTexture1.png");

	for (size_t i = 0; i < 90000; i++)
	{
		{
			Vortex::Object obj = m_Scene.CreateObject();
			obj.AddComponent<Vortex::TransformComponent>();

			auto& renderer2DComponent = obj.AddComponent<Vortex::SpriteComponent>();
			renderer2DComponent.m_Sprite = spiderman;
		}
	}
#endif

	VORTEX_APP_INFO("SCENE SIZE: {0}", m_Scene.size());

	Vortex::FramebufferParams params;
	params.Width = Vortex::ApplicationClass::Get().GetWindow().GetWindowWidth();
	params.Height = Vortex::ApplicationClass::Get().GetWindow().GetWindowHeight();
	m_Framebuffer = Vortex::Framebuffer::Create(params);
}

void ExampleLayer::Input()
{
	glm::vec3 position = m_Camera.GetPosition();
	glm::vec3 rotation = transformComp->GetRotation();
	static float scale = 1.f;

	if (Vortex::Input::IsKeyPressed(Vortex::Key::S)) scale -= 20.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::W)) scale += 20.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::A)) position.x -= 10.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::D)) position.x += 10.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::Q)) position.y -= 10.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::E)) position.y += 10.f * Vortex::Time::GetDeltaTime();

	if (Vortex::Input::IsKeyPressed(Vortex::Key::Up)) rotation.x += 60.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::Down)) rotation.x -= 60.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::Left)) rotation.y += 60.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::Right)) rotation.y -= 60.f * Vortex::Time::GetDeltaTime();

	m_Camera.SetPosition(position);
	transformComp->SetRotation(rotation);
	m_Camera.SetZoom(scale);
}

void ExampleLayer::OnUpdate()
{
	Input();

	m_Framebuffer->Bind();
	Vortex::Renderer2D::BeginScene(m_Camera);
	Vortex::RenderCommand::Clear();

#ifdef BENCH

	for (int i = 0; i < m_Scene.size(); i++)
	{
		Vortex::Object* object = m_Scene[i];
		
		auto& transform = object->GetComponent<Vortex::TransformComponent>();
		auto& finalTransform = transform;

		bool toRender = true;

		const glm::vec4 cameraRect = m_Camera.GetRect();
		const glm::vec3 cameraPos = m_Camera.GetPosition();

		if(transform.GetPosition().x < cameraRect.x + cameraPos.x || transform.GetPosition().x > cameraRect.y + cameraPos.x
	    || transform.GetPosition().y < cameraRect.z + cameraPos.y || transform.GetPosition().y > cameraRect.w + cameraPos.y)
			toRender = false;
		else
			toRender = true;

		if (object->HasComponent<Vortex::SubSpriteComponent>())
		{
			auto& sprite = object->GetComponent<Vortex::SubSpriteComponent>();
			sprite.IsVisible = toRender;

			finalTransform.SetRotation(transformComp->GetRotation());

			if(sprite.IsVisible)
				Vortex::Renderer2D::DrawSubQuad(finalTransform, sprite.m_Sprite, sprite.m_Tint);

		}

		if (object->HasComponent<Vortex::SpriteComponent>())
		{
			auto& sprite = object->GetComponent<Vortex::SpriteComponent>();
			sprite.IsVisible = toRender;
			
			if (sprite.IsVisible)
				Vortex::Renderer2D::DrawQuad(finalTransform, sprite.m_Sprite, sprite.m_TextureTiling, sprite.m_Tint);
		}
	}

#endif

	Vortex::Renderer2D::DrawFromTileMap(m_TileMap, 13, m_TextureMap);

#ifdef BENCH
	float x = 0, y = 0;
	const glm::vec3 cameraPos = m_Camera.GetPosition();
	const glm::vec4 cameraRect = { m_Camera.GetRect().x + cameraPos.x, m_Camera.GetRect().y + cameraPos.x,
								   m_Camera.GetRect().z + cameraPos.y, m_Camera.GetRect().w + cameraPos.y };

	for (int i = 0; i < m_Scene.size(); i++)
	{			
		Vortex::Object* object = m_Scene[i];

		Vortex::TransformComponent& transform = object->GetComponent<Vortex::TransformComponent>();
		transform.SetPosition({ x, y, 0.f });
		transform.SetRotation(transformComp->GetRotation());
		//transform.SetScale({ 0.6f, 0.6f, 0.6f });

		bool toRender = true;

		if (transform.GetPosition().x + transform.GetScale().x / 2.f < cameraRect.x || transform.GetPosition().x - transform.GetScale().x / 2.f > cameraRect.y
		 || transform.GetPosition().y + transform.GetScale().y / 2.f < cameraRect.z || transform.GetPosition().y - transform.GetScale().y / 2.f > cameraRect.w)
			toRender = false;
		else
			toRender = true;

		if (toRender)
		{
			glm::vec4 color = { x / 300.f, 0.4f, y / 300.f, 1.f };
			Vortex::SpriteComponent& sprite = object->GetComponent<Vortex::SpriteComponent>();
			Vortex::Renderer2D::DrawQuad(transform, sprite.m_Sprite, glm::vec2(1.f), color);
		}

		y++;

		if (y == 300)
		{
			x++;
			y = 0;
		}
	}
#endif


	Vortex::Renderer2D::EndScene();
	m_Framebuffer->UnBind();
}

void ExampleLayer::OnEvent(Vortex::Event& event)
{
	m_Camera.OnEvent(event);
}

void ExampleLayer::OnImGuiRender()
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

		ImGui::Begin("Stats");

		ImGui::Text("DeltaTime: %f", Vortex::Time::GetDeltaTime() * 1000.f);

		auto stats = Vortex::Renderer2D::GetStats();
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quad Count: %d", stats.QuadCount);
		ImGui::Text("Vertex Count: %d", stats.GetVertexCount());
		ImGui::Text("Index Count: %d", stats.GetIndexCount());
		ImGui::End();

		ImGui::Begin("Viewport");
		ImGui::Image((void*)m_Framebuffer->GetColorAttachmentID(), { (float)m_Framebuffer->GetParams().Width, (float)m_Framebuffer->GetParams().Height });
		ImGui::End();

		ImGui::End();
	}
}
