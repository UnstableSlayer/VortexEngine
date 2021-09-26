#include "ExampleLayer.h"
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

//#define TEXTURE_TEST
//#define BALLS_TEST
//#define TRANSFORM_PARENT_TEST
//#define TILEMAP_TEST

ExampleLayer::ExampleLayer()
	: Layer("Example")
{
	m_TransformTest.reset(new Vortex::TransformComponent());

	//Camera
	{
		m_Camera = m_Scene.CreateObject();
		auto& transform = m_Camera.AddComponent<Vortex::TransformComponent>();
		auto& camera = m_Camera.AddComponent<Vortex::CameraComponent>(Vortex::CameraType::Perspective, glm::vec2(16.f, 9.f), 1.f, 1000.f, 50.f);
		transform.SetPosition({ 0.f, 0.f, 0.f });
	}

#ifdef TEXTURE_TEST
	//Doom Wall
	{
		Vortex::Object obj = m_Scene.CreateObject();
		obj.AddComponent<Vortex::TagComponent>("DW");
		obj.AddComponent<Vortex::TransformComponent>();

		auto& renderer2DComponent = obj.AddComponent<Vortex::SpriteComponent>();
		renderer2DComponent.m_Texture = Vortex::Texture2D::Create("Textures/4KTest.png", Vortex::TextureFormat::RGB16);
	}
#endif

#ifdef BALLS_TEST
	//Ball
	{
		float radius = 2.f;
		auto& texture = Vortex::Texture2D::Create("Textures/Ball.png", Vortex::TextureFormat::RGBA8);
	
		int count = 16;
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
				transform.SetScale({ 0.2f, 0.2f, 0.2f });
	
				auto& renderer2DComponent = obj.AddComponent<Vortex::SpriteComponent>();
				renderer2DComponent.m_Texture = texture;

				float a = abs(sinf(x)), b = abs(cosf(y));
				renderer2DComponent.m_Tint = { a, b, 0.f, 1.f };
			}
		}

		radius = 5.f;
		count = 32;
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
				transform.SetScale({ 0.5f, 0.5f, 0.5f });

				auto& renderer2DComponent = obj.AddComponent<Vortex::SpriteComponent>();
				renderer2DComponent.m_Texture = texture;

				float a = abs(sinf(x)), b = abs(cosf(y));
				renderer2DComponent.m_Tint = { 0.f, b, a + b, 1.f };
			}
		}

		radius = 15.f;
		count = 64;
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
				renderer2DComponent.m_Tint = { a, 0.f, a + b, 1.f };
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
			childTrans.SetScale(glm::vec3(5.f, 5.f, 5.f) * Vortex::RNG::RandFloat());

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


	if(true)
	{
		using namespace Vortex;

		m_ShipMesh.reset(new Vortex::Mesh());
		m_ShipMesh->Load("Models/PicoShip0.fbx");

		m_ShipVao = VertexArray::Create();

		m_ShipVao->AddVertexBuffer(m_ShipMesh->m_Vertices);
		m_ShipVao->SetIndexBuffer(m_ShipMesh->m_Indices);

		m_ShipShader = Vortex::Shader::Create("Shaders/shipShader.glsl");
	}

}

void ExampleLayer::Input()
{
	auto& transform = m_Camera.GetComponent<Vortex::TransformComponent>();
	auto& camera = m_Camera.GetComponent<Vortex::CameraComponent>();

	glm::vec3 velocity = glm::vec3(0.f);
	glm::vec3 angularVelocity = glm::vec3(0.f);
	static float scale = 1.f;

	if (Vortex::Input::IsKeyPressed(Vortex::Key::I)) scale += 2.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::O)) scale -= 2.f * Vortex::Time::GetDeltaTime();

	if (Vortex::Input::IsKeyPressed(Vortex::Key::S)) velocity.z += 16.f  * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::W)) velocity.z -= 16.f  * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::A)) velocity.x = -20.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::D)) velocity.x =  20.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::Q)) velocity.y = -16.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::E)) velocity.y =  16.f * Vortex::Time::GetDeltaTime();

	{
		bool bMouseLook = Vortex::Input::IsMouseButtonPressed(Vortex::Mouse::ButtonRight);
		static glm::vec2 lastMousePos = glm::vec2(0.f);

		auto& [mousePosX, mousePosY] = Vortex::Input::GetMousePosition();
		if (bMouseLook)
		{
			float deltaX = mousePosY - lastMousePos.y;
			float deltaY = mousePosX - lastMousePos.x;

			angularVelocity.x = 50.f * deltaX * Vortex::Time::GetDeltaTime();
			angularVelocity.y = 50.f * deltaY * Vortex::Time::GetDeltaTime();
		}
		lastMousePos = glm::vec2(mousePosX, mousePosY);
	}

	glm::vec3 forward = glm::vec3(0.f, 0.f, 1.f) * transform.GetRotation();
	glm::vec3 up = glm::vec3(0.f, 1.f, 0.f) * transform.GetRotation();
	glm::vec3 right = glm::vec3(1.f, 0.f, 0.f) * transform.GetRotation();

	transform.Move(velocity.x * right + velocity.y * up + velocity.z * forward);
	transform.Rotate(angularVelocity);
	camera.SetZoom(scale);
}

void ExampleLayer::OnUpdate()
{
	Input();

	Vortex::RenderCommand::Clear();
	//Vortex::Renderer2D::BeginScene(m_Camera);


//	for (size_t i = 1; i < m_Scene.size(); i++)
//	{
//		auto* object = m_Scene[i];
//
//		auto& transform = object->GetComponent<Vortex::TransformComponent>();
//		//transform.SetPosition(m_TransformTest->GetPosition());
//		//transform.SetRotation(m_TransformTest->GetRotation());
//		//auto& test = transform.GetRotation();
//		//VORTEX_APP_INFO("Rot: {0} {1} {2} {3}", test.x, test.y, test.z, test.w);
//
//#ifdef TRANSFORM_PARENT_TEST
//		if (i == 1)
//		{
//			transform.SetPosition(m_TransformTest->GetPosition());
//			transform.SetRotation(m_TransformTest->GetRotation());
//		}
//		else if (i > 1)
//		{
//			float radius = 0.5f * i * transform.GetScale().x;
//			transform.RotateAround({0.f, 0.f, 0.f}, { 0.f, 0.f, 1.f }, radius, i * 10.f * Vortex::Time::GetDeltaTime());
//		}
//#endif
//	}
	//m_Scene.Update(m_Camera.GetComponent<Vortex::TransformComponent>().GetPosition(), Vortex::Time::GetDeltaTime());

#ifdef TILEMAP_TEST
	Vortex::Renderer2D::DrawFromTileMap(m_TileMap, 20, m_TextureMap, m_Color);
#endif

	auto& camera = m_Camera.GetComponent<Vortex::CameraComponent>();
	auto& cameraTransform = m_Camera.GetComponent<Vortex::TransformComponent>();
	
	m_ShipShader->Bind();
	m_ShipShader->SetUniformMat4("uViewProj", camera.GetViewProjectionMatrix(cameraTransform.GetPosition(), cameraTransform.GetRotation()));
	m_ShipVao->Bind();
	Vortex::RenderCommand::DrawIndexed(m_ShipVao, m_ShipVao->GetIndexBuffer()->GetCount());

	//Vortex::Renderer2D::EndScene();
}

void ExampleLayer::OnEvent(Vortex::Event& event)
{
	m_Camera.GetComponent<Vortex::CameraComponent>().OnEvent(event);
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Stats");

	ImGui::Text("DeltaTime: %f", Vortex::Time::GetDeltaTime() * 1000);
	ImGui::Text("FPS: %f", 1.f / Vortex::Time::GetDeltaTime());

	auto stats = Vortex::Renderer2D::GetStats();
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Count: %d", stats.QuadCount);
	ImGui::Text("Vertex Count: %d", stats.GetVertexCount());
	ImGui::Text("Index Count: %d", stats.GetIndexCount());

	ImGui::ColorPicker4("Light", (float*)&m_Color);

	ImGui::End();


	ImGui::Begin("Camera");

	auto& transform = m_Camera.GetComponent<Vortex::TransformComponent>();
	auto& camera = m_Camera.GetComponent<Vortex::CameraComponent>();
	ImGui::Text("POS: %f %f %f", transform.GetPosition().x, transform.GetPosition().y, transform.GetPosition().z);
	ImGui::Text("ROT: %f %f %f %f", transform.GetRotation().x, transform.GetRotation().y, transform.GetRotation().z, transform.GetRotation().w);
	ImGui::Text("CLIPPING: %f %f", camera.GetClipSpace().x, camera.GetClipSpace().y);
	ImGui::Text("ZOOM: %f", camera.GetZoom());

	ImGui::End();

}
 