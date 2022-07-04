#include "ExampleLayer.h"
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

//#define TEXTURE_TEST
//#define BALLS_TEST
//#define TRANSFORM_PARENT_TEST
#define TILEMAP_TEST
//#define SHIP_TEST

ExampleLayer::ExampleLayer()
	: Layer("Example")
{
    VORTEX_APP_INFO("LayerInit started!");

	m_TransformTest = Vortex::MakeRef<Vortex::TransformComponent>();

	//Camera
	{
		m_Camera = m_Scene.CreateObject();
		auto& transform = m_Camera.AddComponent<Vortex::TransformComponent>();
		Vortex::Transform::SetPosition(transform, { 0.f, 0.f, 10.f });

		m_Camera.AddComponent<Vortex::CameraController>(Vortex::CameraType::Perspective, 16.f, 9.f, 0.1f, 10000.f, 55.f);
	}

#ifdef TEXTURE_TEST
	//Doom Wall
	{
		Vortex::Object obj = m_Scene.CreateObject();
		obj.AddComponent<Vortex::TagComponent>("DW");
		auto& transform = obj.AddComponent<Vortex::TransformComponent>();
		Vortex::Transform::SetPosition(transform, {0.f, 0.f, 0.f});

		auto& renderer2DComponent = obj.AddComponent<Vortex::SpriteComponent>();
		renderer2DComponent.m_Texture = Vortex::Texture2D::Create("Textures/testTexture0.png", Vortex::TextureFormat::RGB16);
	}

	//Spiderman
	{
		Vortex::Object obj = m_Scene.CreateObject();
		obj.AddComponent<Vortex::TagComponent>("SP");
		auto& transform = obj.AddComponent<Vortex::TransformComponent>();
		Vortex::Transform::SetPosition(transform, { -1.f, 0.f, 0.f });

		auto& renderer2DComponent = obj.AddComponent<Vortex::SpriteComponent>();
		renderer2DComponent.m_Texture = Vortex::Texture2D::Create("Textures/testTexture1.png", Vortex::TextureFormat::RGBA16);
	}

	//Skull
	{
		Vortex::Object obj = m_Scene.CreateObject();
		obj.AddComponent<Vortex::TagComponent>("SK");
		auto& transform = obj.AddComponent<Vortex::TransformComponent>();
		Vortex::Transform::SetPosition(transform, { 0.f, 1.f, 0.f });

		auto& renderer2DComponent = obj.AddComponent<Vortex::SpriteComponent>();
		renderer2DComponent.m_Texture = Vortex::Texture2D::Create("Textures/testTexture.png", Vortex::TextureFormat::RGBA16);
	}

	//Bricks
	{
		Vortex::Object obj = m_Scene.CreateObject();
		obj.AddComponent<Vortex::TagComponent>("BR");
		auto& transform = obj.AddComponent<Vortex::TransformComponent>();
		Vortex::Transform::SetPosition(transform, { 0.f, 0.f, -10.f });
	
		auto& renderer2DComponent = obj.AddComponent<Vortex::SpriteComponent>();
		renderer2DComponent.m_Texture = Vortex::Texture2D::Create("Textures/bricks.png", Vortex::TextureFormat::RGB16);
	}

#endif

#ifdef BALLS_TEST
	//Ball
	{
		float radius = 20.f;
		auto texture = Vortex::Texture2D::Create("Textures/Ball.png", Vortex::TextureFormat::RGBA8);

		int count = 32;
		for (size_t x = 0; x < count; x++)
		{
			for (size_t y = 0; y < count; y++)
			{
				Vortex::Object obj = m_Scene.CreateObject();
				obj.AddComponent<Vortex::TagComponent>("Ball");
				Vortex::TransformComponent& transform = obj.AddComponent<Vortex::TransformComponent>();
				float angleX = ((360.f / (count)) * x);
				float angleY = ((360.f / (count)) * y);
				Vortex::Transform::SetPosition(transform, { radius * cosf(angleX) * sinf(angleY) + 0.1f * x,
					                                        radius * sinf(angleX) * sinf(angleY) + 0.1f * y,
										                    radius * cosf(angleY) + 0.1f * y * x });
				Vortex::Transform::SetScale(transform, { 0.2f, 0.2f, 0.2f });

				auto& renderer2DComponent = obj.AddComponent<Vortex::SpriteComponent>();
				renderer2DComponent.m_Texture = texture;

				float a = abs(sinf(x)), b = abs(cosf(y));
				renderer2DComponent.m_Tint = { a, b, 0.f, 1.f };
			}
		}

// 		radius = 5.f;
// 		count = 32;
// 		for (size_t x = 0; x < count; x++)
// 		{
// 			for (size_t y = 0; y < count; y++)
// 			{
// 				Vortex::Object obj = m_Scene.CreateObject();
// 				obj.AddComponent<Vortex::TagComponent>("Ball");
// 				Vortex::TransformComponent& transform = obj.AddComponent<Vortex::TransformComponent>();
// 				float angleX = ((360.f / (count)) * x);
// 				float angleY = ((360.f / (count)) * y);
// 				transform.SetPosition({ radius * cosf(angleX) * sinf(angleY) + 0.001f * x,
// 										radius * sinf(angleX) * sinf(angleY) + 0.001f * y,
// 										radius * cosf(angleY) + 0.0001f * y * x });
// 				transform.SetScale({ 0.5f, 0.5f, 0.5f });
//
// 				auto& renderer2DComponent = obj.AddComponent<Vortex::SpriteComponent>();
// 				renderer2DComponent.m_Texture = texture;
//
// 				float a = abs(sinf(x)), b = abs(cosf(y));
// 				renderer2DComponent.m_Tint = { 0.f, b, a + b, 1.f };
// 			}
// 		}
//
// 		radius = 15.f;
// 		count = 64;
// 		for (size_t x = 0; x < count; x++)
// 		{
// 			for (size_t y = 0; y < count; y++)
// 			{
// 				Vortex::Object obj = m_Scene.CreateObject();
// 				obj.AddComponent<Vortex::TagComponent>("Ball");
// 				Vortex::TransformComponent& transform = obj.AddComponent<Vortex::TransformComponent>();
// 				float angleX = ((360.f / (count)) * x);
// 				float angleY = ((360.f / (count)) * y);
// 				transform.SetPosition({ radius * cosf(angleX) * sinf(angleY) + 0.001f * x,
// 										radius * sinf(angleX) * sinf(angleY) + 0.001f * y,
// 										radius * cosf(angleY) + 0.0001f * y * x });
//
// 				auto& renderer2DComponent = obj.AddComponent<Vortex::SpriteComponent>();
// 				renderer2DComponent.m_Texture = texture;
//
// 				float a = abs(sinf(x)), b = abs(cosf(y));
// 				renderer2DComponent.m_Tint = { a, 0.f, a + b, 1.f };
// 			}
// 		}
	}
#endif

#ifdef TRANSFORM_PARENT_TEST
	{
		auto texture = Vortex::Texture2D::Create("Textures/Ball.png", Vortex::TextureFormat::RGBA16);

		auto& parentObj = m_Scene.CreateObject();
		auto& parentTrans = parentObj.AddComponent<Vortex::TransformComponent>();
		Vortex::Transform::SetPosition(parentTrans, { 0.f, 0.f, 0.f });
		Vortex::Transform::SetScale(parentTrans, { 10.f, 10.f, 10.f });

		auto& parentSprite = parentObj.AddComponent<Vortex::SpriteComponent>();
		parentSprite.m_Texture = texture;
		parentSprite.m_Tint = { 1.f, 0.f, 0.f, 1.f };

		Vortex::Object temp = parentObj;

		for (int i = 0; i < 10; i++)
		{
			auto& childObj = m_Scene.CreateObject();
			auto& childTrans = childObj.AddComponent<Vortex::TransformComponent>();
			Vortex::Transform::SetParent(childTrans, temp);
			Vortex::Transform::SetScale(childTrans, glm::vec3(5.f, 5.f, 5.f) * Vortex::RNG::RandFloat());

			if(i % 3 == 0) temp = childObj;
			else    temp = parentObj;

			auto& childSprite = childObj.AddComponent<Vortex::SpriteComponent>();
			childSprite.m_Texture = texture;
			childSprite.m_Tint = glm::vec4(Vortex::RNG::RandFloat(), Vortex::RNG::RandFloat(), Vortex::RNG::RandFloat(), 1.f);
		}
	}
#endif

#ifdef TILEMAP_TEST
	{
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

		Vortex::Ref<Vortex::Texture2D> atlasTex = Vortex::Texture2D::Create("Textures/Set_A_Standard_Coast.png", Vortex::TextureFormat::RGBA16);
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
		m_ShipMesh->Load("Models/Ship0.fbx");

		m_ShipVao = m_ShipMesh->m_Data;

		m_ShipTexture = Vortex::Texture2D::Create("Textures/Ship0.png", Vortex::TextureFormat::RGBA16, Vortex::TextureWrap::REPEAT);
		m_ShipTexture->MakeHandleResident();

		m_ShipShader = Vortex::Shader::Create("Shaders/litShaderBindless.glsl");

		m_ShipShader->Bind();
		m_ShipShader->SetUniformTexHandle("uTexture", m_ShipTexture->GetBindlessHandle());
	}

	//VORTEX_APP_INFO("DeltaTime: {0}", Vortex::Time::GetDeltaTime());
#endif

    VORTEX_APP_INFO("LayerInit done!");
}

void ExampleLayer::Input()
{
	auto& transform = m_Camera.GetComponent<Vortex::TransformComponent>();
	auto& camera = m_Camera.GetComponent<Vortex::CameraController>();

	glm::vec3 velocity = glm::vec3(0.f);
	glm::vec3 angularVelocity = glm::vec3(0.f);
	float scale = camera.m_Camera.m_Zoom;

	if (Vortex::Input::IsKeyPressed(Vortex::Key::I)) scale += 10.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::O)) scale -= 10.f * Vortex::Time::GetDeltaTime();

	if (Vortex::Input::IsKeyPressed(Vortex::Key::S)) velocity.z += 10.f  * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::W)) velocity.z -= 10.f  * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::A)) velocity.x = -20.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::D)) velocity.x =  20.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::Q)) velocity.y = -10.f * Vortex::Time::GetDeltaTime();
	if (Vortex::Input::IsKeyPressed(Vortex::Key::E)) velocity.y =  10.f * Vortex::Time::GetDeltaTime();

	if (Vortex::Input::IsKeyPressed(Vortex::Key::ESC)) Vortex::ApplicationClass::Get().GetWindow().LockCursor(false);
	if (Vortex::Input::IsMouseButtonPressed(Vortex::Mouse::L)) Vortex::ApplicationClass::Get().GetWindow().LockCursor(true);

	{
		auto [mouseDeltaX, mouseDeltaY] = Vortex::Input::GetMouseDelta();
		{
			float deltaX = mouseDeltaY;
			float deltaY = mouseDeltaX;

			angularVelocity.x = 0.1f * deltaX;// * Vortex::Time::GetDeltaTime();
			angularVelocity.y = 0.1f * deltaY;// * Vortex::Time::GetDeltaTime();
		}
	}

	glm::vec3 forward = glm::vec3(0.f, 0.f, 1.f) * transform.m_Rotation;
	glm::vec3 up =		glm::vec3(0.f, 1.f, 0.f) * transform.m_Rotation;
	glm::vec3 right =	glm::vec3(1.f, 0.f, 0.f) * transform.m_Rotation;

	Vortex::Transform::Move(transform, velocity.x * right + velocity.y * up + velocity.z * forward);
	Vortex::Transform::Rotate(transform, angularVelocity);

	//Hack for now
	Vortex::Camera::PerspectiveZoom(camera.m_Camera, scale);
}

void ExampleLayer::OnUpdate()
{
	Input();

	Vortex::Renderer2D::BeginScene(m_Camera);
	Vortex::RenderCommand::Clear();

    #ifdef TRANSFORM_PARENT_TEST
	for (size_t i = 1; i < m_Scene.size(); i++)
	{
		auto* object = m_Scene[i];

		auto& transform = object->GetComponent<Vortex::TransformComponent>();
		//transform.SetPosition(m_TransformTest->GetPosition());
		//transform.SetRotation(m_TransformTest->GetRotation());
		//auto& test = transform.GetRotation();
		//VORTEX_APP_INFO("Rot: {0} {1} {2} {3}", test.x, test.y, test.z, test.w);

		if (i == 1)
		{
			Vortex::Transform::SetPosition(transform, m_TransformTest->m_Position);
			Vortex::Transform::SetRotation(transform, m_TransformTest->m_Rotation);
		}
		else if (i > 1)
		{
			float radius = i + transform.m_Scale.x;
			Vortex::Transform::RotateAround(transform, {0.f, 0.f, 0.f}, { 0.f, 0.f, 1.f }, radius, i * 10.f * Vortex::Time::GetDeltaTime());
			Vortex::Transform::SetPosition(transform, { transform.m_Position.x, transform.m_Position.y, i});
		}
	}
	#endif

	m_Scene.Update(m_Camera.GetComponent<Vortex::TransformComponent>().m_Position, Vortex::Time::GetDeltaTime());

	#ifdef TILEMAP_TEST
		Vortex::Renderer2D::DrawFromTileMap(m_TileMap, 20, m_TextureMap, m_Color);
	#endif

    #ifdef SHIP_TEST
	auto& cameractrl = m_Camera.GetComponent<Vortex::CameraController>();
	auto& cameraTransform = m_Camera.GetComponent<Vortex::TransformComponent>();

	m_ShipShader->Bind();
	Vortex::Camera::RecalculateViewMatrix(cameractrl.m_Camera, cameraTransform.m_Position, cameraTransform.m_Rotation);
	m_ShipShader->SetUniformMat4("uViewProj", cameractrl.m_Camera.m_ViewProjectionMatrix);

	//m_ShipTexture->Bind(1);
	m_ShipVao->Bind();
	Vortex::RenderCommand::DrawIndexed(m_ShipVao, m_ShipVao->GetIndexBuffer()->GetCount());
    #endif

	Vortex::Renderer2D::EndScene();
}

void ExampleLayer::OnEvent(Vortex::Event& event)
{
	m_Camera.GetComponent<Vortex::CameraController>().OnEvent(event);
} 
