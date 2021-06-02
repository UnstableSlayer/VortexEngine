#include "ExampleLayer.h"

#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
	: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
	transformComp.reset(new Vortex::TransformComponent());

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
}

void ExampleLayer::Input()
{
	glm::vec3 position = m_Camera.GetPosition();
	glm::vec3 rotation = transformComp->GetRotation();
	static float scale = 1.f;

	if (Vortex::Input::IsKeyPressed(Vortex::Key::S)) scale -= 4.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::W)) scale += 4.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::A)) position.x -= 2.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::D)) position.x += 2.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::Q)) position.y -= 2.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::E)) position.y += 2.f * Vortex::Time::GetDeltaTime();

	if (Vortex::Input::IsKeyPressed(Vortex::Key::Up)) rotation.x += 60.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::Down)) rotation.x -= 60.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::Left)) rotation.y += 60.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::Right)) rotation.y -= 60.f * Vortex::Time::GetDeltaTime();

	/*m_Camera.SetPosition(position);
	m_Camera.SetRotation(rotation);
	m_Camera.SetZoom(scale);*/
	
	m_Camera.SetPosition(position);
	transformComp->SetRotation(rotation);
	m_Camera.SetZoom(scale);
}

void ExampleLayer::OnUpdate()
{
	Input();

	Vortex::Renderer2D::BeginScene(m_Camera);
	Vortex::RenderCommand::Clear();

	for (int i = 0; i < m_Scene.size(); i++)
	{
		Vortex::Scope<Vortex::Object> object = m_Scene[i];

		if (object->HasComponent<Vortex::SpriteComponent>() && object->GetComponent<Vortex::SpriteComponent>().IsVisible)
		{
			auto& obj = object->GetComponent<Vortex::SpriteComponent>();

			Vortex::TransformComponent& transform = object->GetComponent<Vortex::TransformComponent>();
			Vortex::TransformComponent& finalTransform = transform;
			
			
			if(object->HasComponent<Vortex::TagComponent>() && object->GetComponent<Vortex::TagComponent>().m_Tag != "bg0")
				finalTransform.SetRotation(transformComp->GetRotation());

			Vortex::Renderer2D::DrawQuad(finalTransform, obj.m_Sprite, obj.m_TextureTiling, obj.m_Tint);
		}
	}

	//for (float x = 0; x < 20.0f; x+=0.25f)
	//{
	//	for(float y = 0.f; y < 20.f; y += 0.25f)
	//	{ 
	//		Vortex::TransformComponent transform = Vortex::TransformComponent();
	//		transform.SetPosition({ x, y, 0.f });
	//		transform.SetRotation(transformComp->GetRotation());
	//		transform.SetScale({ 0.6f, 0.6f, 0.6f });

	//		Vortex::Renderer2D::DrawQuad(transform, { x / 20.f, y / 20.f, 0.f, 1.f });
	//	}
	//}

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

	ImGui::Begin("Color");
	ImGui::ColorPicker4("QuadColor", glm::value_ptr(color));
	ImGui::End();
}
