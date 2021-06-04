#include "ExampleLayer.h"
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

//#define BASIC_TEST
#define TILEMAP_TEST
//#define BENCH

//#define CULLING_TEST


ExampleLayer::ExampleLayer()
	: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
{

#ifdef BASIC_TEST
	//Doom Wall
	{
		Vortex::Object obj = m_Scene.CreateObject();
		obj.AddComponent<Vortex::TagComponent>("DW");
		obj.AddComponent<Vortex::TransformComponent>();

		auto& renderer2DComponent = obj.AddComponent<Vortex::SpriteComponent>();
		renderer2DComponent.m_Sprite = Vortex::Texture2D::Create("Textures/testTexture0.png");
	}

	//Skull
	{
		Vortex::Object obj = m_Scene.CreateObject();
		obj.AddComponent<Vortex::TagComponent>("SK");

		auto& transform = obj.AddComponent<Vortex::TransformComponent>();
		transform.SetPosition({ 1.f, -2.f, 0.f });
		
		auto& renderer2DComponent = obj.AddComponent<Vortex::SpriteComponent>();
		renderer2DComponent.m_Sprite = Vortex::Texture2D::Create("Textures/testTexture.png");
	}

	//Spiderman
	{
		Vortex::Object obj = m_Scene.CreateObject();
		obj.AddComponent<Vortex::TagComponent>("SM");

		auto& transform = obj.AddComponent<Vortex::TransformComponent>();
		transform.SetPosition({ -2.f, 1.f, 0.f });

		auto& renderer2DComponent = obj.AddComponent<Vortex::SpriteComponent>();
		renderer2DComponent.m_Sprite = Vortex::Texture2D::Create("Textures/testTexture1.png");
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
#endif

#ifdef TILEMAP_TEST
	m_TileMap = "0000111110000"
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
}

void ExampleLayer::Input()
{
	glm::vec3 position = m_Camera.GetPosition();
	glm::vec3 rotation = m_Camera.GetRotation();
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
	m_Camera.SetRotation(rotation);
	m_Camera.SetZoom(scale);
}

void ExampleLayer::OnUpdate()
{
	Input();

	Vortex::RenderCommand::Clear();
	Vortex::Renderer2D::BeginScene(m_Camera);

#ifdef BASIC_TEST

	for (int i = 0; i < m_Scene.size(); i++)
	{
		Vortex::Object* object = m_Scene[i];
		
		auto& transform = object->GetComponent<Vortex::TransformComponent>();

		bool toRender = true;

#ifdef CULLING_TEST
		const glm::vec4 cameraRect = m_Camera.GetRect();
		const glm::vec3 cameraPos = m_Camera.GetPosition();

		if(transform.GetPosition().x < cameraRect.x + cameraPos.x || transform.GetPosition().x > cameraRect.y + cameraPos.x
	    || transform.GetPosition().y < cameraRect.z + cameraPos.y || transform.GetPosition().y > cameraRect.w + cameraPos.y)
			toRender = false;
		else
			toRender = true;
#endif

		if (object->HasComponent<Vortex::SubSpriteComponent>())
		{
			auto& sprite = object->GetComponent<Vortex::SubSpriteComponent>();
			sprite.IsVisible = toRender;

			if(sprite.IsVisible)
				Vortex::Renderer2D::DrawSubQuad(transform, sprite.m_Sprite, sprite.m_Tint);

		}

		if (object->HasComponent<Vortex::SpriteComponent>())
		{
			auto& sprite = object->GetComponent<Vortex::SpriteComponent>();
			sprite.IsVisible = toRender;
			
			if (sprite.IsVisible)
				Vortex::Renderer2D::DrawQuad(transform, sprite.m_Sprite, sprite.m_TextureTiling, sprite.m_Tint);
		}
	}

#endif

#ifdef TILEMAP_TEST
	Vortex::Renderer2D::DrawFromTileMap(m_TileMap, 13, m_TextureMap);
#endif

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
		transform.SetRotation({ x * Vortex::RNG::RandFloat(), y * Vortex::RNG::RandFloat(), (y - x) * Vortex::RNG::RandFloat()});
		//transform.SetScale({ 0.6f, 0.6f, 0.6f });

		bool toRender = true;

#ifdef CULLING_TEST
		if (transform.GetPosition().x + transform.GetScale().x / 2.f < cameraRect.x || transform.GetPosition().x - transform.GetScale().x / 2.f > cameraRect.y
		 || transform.GetPosition().y + transform.GetScale().y / 2.f < cameraRect.z || transform.GetPosition().y - transform.GetScale().y / 2.f > cameraRect.w)
			toRender = false;
		else
			toRender = true;
#endif
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
}

void ExampleLayer::OnEvent(Vortex::Event& event)
{
	m_Camera.OnEvent(event);
}

void ExampleLayer::OnImGuiRender()
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
