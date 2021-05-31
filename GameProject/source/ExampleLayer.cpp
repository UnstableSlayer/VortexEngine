#include "ExampleLayer.h"

#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
	: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
	Vortex::Object obj = m_Scene.CreateObject();
	obj.AddComponent<Vortex::TransformComponent>();

	testTexture = Vortex::Texture2D::Create("Textures/testTexture0.png");
}

void ExampleLayer::OnUpdate()
{
	static Vortex::TransformComponent& transform = m_Scene[0]->GetComponent<Vortex::TransformComponent>();

	static glm::vec3 position = glm::vec3(0.f), rotation = glm::vec3(0.f);
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

	m_Camera.SetPosition(position);
	m_Camera.SetRotation(rotation);
	m_Camera.SetZoom(scale);


	Vortex::Renderer2D::BeginScene(m_Camera);
	Vortex::RenderCommand::Clear(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

	Vortex::Renderer2D::DrawQuad(transform, *testTexture, glm::vec2(1.f), color);
	Vortex::Renderer2D::EndScene();
}

void ExampleLayer::OnEvent(Vortex::Event& event)
{
	m_Camera.OnEvent(event);
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Color");
	ImGui::ColorPicker4("QuadColor", glm::value_ptr(color));
	ImGui::End();
}
