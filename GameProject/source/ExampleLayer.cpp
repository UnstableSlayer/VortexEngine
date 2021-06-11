#include "ExampleLayer.h"
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

//#define BALLS_TEST
//#define TRANSFORM_PARENT_TEST
#define TILEMAP_TEST

ExampleLayer::ExampleLayer()
	: Layer("Example")
{
	m_TransformTest.reset(new Vortex::TransformComponent());

	//Camera
	{
		m_Camera = m_Scene.CreateObject();
		auto& transform = m_Camera.AddComponent<Vortex::TransformComponent>();
		auto& camera = m_Camera.AddComponent<Vortex::CameraComponent>(Vortex::CameraType::Perspective, glm::vec2(16.f, 9.f), -1.f, 100.f);
		transform.SetPosition({ 0.f, 0.f, 0.f });
	}

#ifdef BALLS_TEST
	//Ball
	{
		float radius = 10.f;
		auto& texture = Vortex::Texture2D::Create("Textures/Ball.png");
	
		int count = 100;
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

				float a = abs(sinf(x)), b = abs(cosf(y));
				renderer2DComponent.m_Tint = { a, b, 0.8f, a+b };
			}
		}
	}
#endif

#ifdef TRANSFORM_PARENT_TEST
	{
		auto& texture = Vortex::Texture2D::Create("Textures/Ball.png");

		auto& parentObj = m_Scene.CreateObject();
		auto& parentTrans = parentObj.AddComponent<Vortex::TransformComponent>();
		parentTrans.SetPosition({ 0.f, 0.f, 0.f });
		parentTrans.SetScale({ 10.f, 10.f, 10.f });

		auto& parentSprite = parentObj.AddComponent<Vortex::SpriteComponent>();
		parentSprite.m_Texture = texture;
		parentSprite.m_Tint = { 1.f, 0.f, 0.f, 1.f };

		for(int i = 0; i < 10; i++)
		{
			auto& childObj = m_Scene.CreateObject();
			auto& childTrans = childObj.AddComponent<Vortex::TransformComponent>();
			childTrans.SetParent(parentObj);
			childTrans.SetScale(glm::vec3(0.6f, 0.6f, 0.6f) * Vortex::RNG::RandFloat());

			auto& childSprite = childObj.AddComponent<Vortex::SpriteComponent>();
			childSprite.m_Texture = texture;
			childSprite.m_Tint = glm::vec4(Vortex::RNG::RandFloat(), Vortex::RNG::RandFloat(), Vortex::RNG::RandFloat(), 1.f);
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

	if (Vortex::Input::IsKeyPressed(Vortex::Key::Up)) rotation.x = 80.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::Down)) rotation.x = -60.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::Left)) rotation.z = 60.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::Right)) rotation.z = -60.f * Vortex::Time::GetDeltaTime();

	m_TransformTest->Move(position);
	m_TransformTest->Rotate(rotation);
	camera.SetZoom(scale);
}

void ExampleLayer::OnUpdate()
{
	Input();

	Vortex::RenderCommand::Clear();
	Vortex::Renderer2D::BeginScene(m_Camera);

	for (size_t i = 0; i < m_Scene.size(); i++)
	{
		auto* object = m_Scene[i];

		auto& transform = object->GetComponent<Vortex::TransformComponent>();

#ifdef TRANSFORM_PARENT_TEST
		if (i == 1)
		{
			transform.SetPosition(m_TransformTest->GetPosition());
			transform.SetRotation(m_TransformTest->GetRotation());
		}
		else if (i > 1)
		{
			float radius = 4.f * i * transform.GetScale().x + transform.GetParent()->GetScale().x / 2.f + 10.f;
			transform.RotateAround({0.f, 0.f, 0.f}, { 0.f, 0.f, 1.f }, radius, i * 10.f * Vortex::Time::GetDeltaTime());
		}
#endif

		if (object->HasComponent<Vortex::SpriteComponent>())
		{
			auto& spriteComp = object->GetComponent<Vortex::SpriteComponent>();
			Vortex::Renderer2D::DrawQuad(transform, spriteComp, spriteComp.m_Tint * m_Color);
		}
		
		if (object->HasComponent<Vortex::SubSpriteComponent>())
		{
			auto& subSpriteComp = object->GetComponent<Vortex::SubSpriteComponent>();
			Vortex::Renderer2D::DrawSubQuad(transform, subSpriteComp.m_Sprite, subSpriteComp.m_Tint * m_Color);
		}
	}

#ifdef TILEMAP_TEST
	Vortex::Renderer2D::DrawFromTileMap(m_TileMap, 20, m_TextureMap, m_Color);
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

	ImGui::ColorPicker4("Light", (float*)&m_Color);
	ImGui::End();
}
 