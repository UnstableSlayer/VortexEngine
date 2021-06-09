#include "ExampleLayer.h"
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

//#define BALL_TEST
#define TILEMAP_TEST

ExampleLayer::ExampleLayer()
	: Layer("Example")

{
	//Camera
	{
		m_Camera = m_Scene.CreateObject();
		auto& transform = m_Camera.AddComponent<Vortex::TransformComponent>();
		auto& camera = m_Camera.AddComponent<Vortex::CameraComponent>(Vortex::CameraType::Orthographical, glm::vec2(16.f, 9.f), -1.f, 100.f);
		transform.SetPosition({ 0.f, 0.f, 0.f });
	}

#ifdef BALLS_TEST
	//Ball
	{
		float radius = 10.f;
		auto& texture = Vortex::Texture2D::Create("Textures/Ball.png");
	
		int count = 128;
		for (size_t x = 0; x < count; x++)
		{
			for (size_t y = 0; y < count; y++)
			{
				Vortex::Object obj = m_Scene.CreateObject();
				obj.AddComponent<Vortex::TagComponent>("Ball");
				Vortex::TransformComponent& transform = obj.AddComponent<Vortex::TransformComponent>();
				float angleX = ((360.f / (count)) * x);
				float angleY = ((360.f / (count)) * y);
				transform.SetPosition({ radius * cosf(angleX) * sinf(angleY),
										radius * sinf(angleX) * sinf(angleY),
										radius * cosf(angleY) });
	
				auto& renderer2DComponent = obj.AddComponent<Vortex::SpriteComponent>();
				renderer2DComponent.m_Texture = texture;
			}
		}
	}
#endif

#ifdef TILEMAP_TEST
	m_TileMap = "31111111111111111119"
		"20000000000000000008"
		"20000000000000000008"
		"20000000000000000008"
		"20000000000000000008"
		"20000000000000000008"
		"20000000000000000008"
		"20000000000000000008"
		"20000000000000000008"
		"20000000000000000008"
		"20000000000000000008"
		"20000000000000000008"
		"20000000000000000008"
		"20000000000000000008"
		"20000000000000000008"
		"20000000000000000008"
		"20000000000000000008"
		"20000000000000000008"
		"20000000000000000008"
		"6444444444444444444c";


	m_TextureMap.insert({ '0', Vortex::SubTexture2D::CreateFromPos(Vortex::Texture2D::Create("Textures/Set_A_Standard_Coast.png"), { 1, 14 }, { 16, 16 }) });
	m_TextureMap.insert({ '1', Vortex::SubTexture2D::CreateFromPos(Vortex::Texture2D::Create("Textures/Set_A_Standard_Coast.png"), { 1, 15 }, { 16, 16 }) });
	m_TextureMap.insert({ '3', Vortex::SubTexture2D::CreateFromPos(Vortex::Texture2D::Create("Textures/Set_A_Standard_Coast.png"), { 0, 15 }, { 16, 16 }) });
	m_TextureMap.insert({ '2', Vortex::SubTexture2D::CreateFromPos(Vortex::Texture2D::Create("Textures/Set_A_Standard_Coast.png"), { 0, 14 }, { 16, 16 }) });
	m_TextureMap.insert({ '6', Vortex::SubTexture2D::CreateFromPos(Vortex::Texture2D::Create("Textures/Set_A_Standard_Coast.png"), { 0, 13 }, { 16, 16 }) });
	m_TextureMap.insert({ '4', Vortex::SubTexture2D::CreateFromPos(Vortex::Texture2D::Create("Textures/Set_A_Standard_Coast.png"), { 1, 13 }, { 16, 16 }) });
	m_TextureMap.insert({ 'c', Vortex::SubTexture2D::CreateFromPos(Vortex::Texture2D::Create("Textures/Set_A_Standard_Coast.png"), { 2, 13 }, { 16, 16 }) });
	m_TextureMap.insert({ '8', Vortex::SubTexture2D::CreateFromPos(Vortex::Texture2D::Create("Textures/Set_A_Standard_Coast.png"), { 2, 14 }, { 16, 16 }) });
	m_TextureMap.insert({ '9', Vortex::SubTexture2D::CreateFromPos(Vortex::Texture2D::Create("Textures/Set_A_Standard_Coast.png"), { 2, 15 }, { 16, 16 }) });
#endif
}

void ExampleLayer::Input()
{
	auto& transform = m_Camera.GetComponent<Vortex::TransformComponent>();
	auto& camera = m_Camera.GetComponent<Vortex::CameraComponent>();

	glm::vec3 position = glm::vec3(0.f);
	glm::vec3 rotation = glm::vec3(0.f);
	static float scale = 0.f;

	if (Vortex::Input::IsKeyPressed(Vortex::Key::S)) scale += 5.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::W)) scale -= 5.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::A)) position.x = -10.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::D)) position.x = 10.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::Q)) position.y = -10.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::E)) position.y = 10.f * Vortex::Time::GetDeltaTime();

	if (Vortex::Input::IsKeyPressed(Vortex::Key::Up)) rotation.x = 60.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::Down)) rotation.x = -60.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::Left)) rotation.y = 60.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::Right)) rotation.y = -60.f * Vortex::Time::GetDeltaTime();

	transform.Move(position);
	transform.Rotate(rotation);
	camera.SetZoom(scale);
}

void ExampleLayer::OnUpdate()
{
	Input();

	Vortex::RenderCommand::Clear({ 0.1f, 0.1f, 0.1f, 1.f });
	Vortex::Renderer2D::BeginScene(m_Camera);

	for (size_t i = 0; i < m_Scene.size(); i++)
	{
		Vortex::Object* object = m_Scene[i];

		Vortex::TransformComponent& transform = object->GetComponent<Vortex::TransformComponent>();

		if (object->HasComponent<Vortex::SpriteComponent>())
		{
			Vortex::SpriteComponent& spriteComp = object->GetComponent<Vortex::SpriteComponent>();
			Vortex::Renderer2D::DrawQuad(transform, spriteComp, spriteComp.m_Tint * color);
		}
		
		if (object->HasComponent<Vortex::SubSpriteComponent>())
		{
			Vortex::SubSpriteComponent& subSpriteComp = object->GetComponent<Vortex::SubSpriteComponent>();
			Vortex::Renderer2D::DrawSubQuad(transform, subSpriteComp.m_Sprite, subSpriteComp.m_Tint * color);
		}
	}

#ifdef TILEMAP_TEST
	Vortex::Renderer2D::DrawFromTileMap(m_TileMap, 20, m_TextureMap, color);
#endif

	Vortex::Renderer2D::EndScene();
}

void ExampleLayer::OnEvent(Vortex::Event& event)
{
	m_Camera.GetComponent<Vortex::CameraComponent>().OnEvent(event);
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Stats");

	ImGui::Text("DeltaTime: %f", Vortex::Time::GetDeltaTime() * 1000.f);
	ImGui::Text("FPS: %f", 1.f / Vortex::Time::GetDeltaTime());

	auto stats = Vortex::Renderer2D::GetStats();
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Count: %d", stats.QuadCount);
	ImGui::Text("Vertex Count: %d", stats.GetVertexCount());
	ImGui::Text("Index Count: %d", stats.GetIndexCount());

	ImGui::ColorPicker4("Light", (float*)&color);
	ImGui::End();
}
 