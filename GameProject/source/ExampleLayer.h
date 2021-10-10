#pragma once
#include <string>
#include <sstream>
#include <functional>
#include <chrono>

#include <VortexEngine.h>

class ExampleLayer : public Vortex::Layer
{
public:
	ExampleLayer();

	void Input();

	virtual void OnUpdate() override;

	virtual void OnEvent(Vortex::Event& event) override;

private:
	Vortex::Scene m_Scene;
	Vortex::Object m_Camera;

	std::unordered_map<char, Vortex::Ref<Vortex::SubTexture2D>> m_TextureMap;
	const char* m_TileMap;

	Vortex::Ref<Vortex::TransformComponent> m_TransformTest;

	glm::vec4 m_Color = glm::vec4(1.f);

	Vortex::Ref<Vortex::Mesh> m_ShipMesh;
	Vortex::Ref<Vortex::VertexArray> m_ShipVao;
	Vortex::Ref<Vortex::Shader> m_ShipShader;
	Vortex::Ref<Vortex::Texture2D> m_ShipTexture;
};