#include "WorldLayer.h"
#include "Environment/ComponentModifiers.h"
#include "Environment/Components.h"
#include <iostream>
WorldLayer::WorldLayer() : Layer("WorldLayer")
{
    std::string tileMapStr;
    tileMapStr= "31111111111111111119\n"
                "20000000000000000008\n"
                "20000000000000000008\n"
                "20000000000000000008\n"
                "20000000000000000008\n"
                "20000000000000000008\n"
                "20000000000000000008\n"
                "200000000  000000008\n"
                "200000      00000008\n"
                "200000      00000008\n"
                "2000000    000000008\n"
                "200000000 0000000008\n"
                "20000000000000000008\n"
                "20000000000000000008\n"
                "20000000000000000008\n"
                "20000000000000000008\n"
                "20000000000000000008\n"
                "20000000000000000008\n"
                "20000000000000000008\n"
                "6444444444444444444c";

    //std::cin >> tileMapStr;
	Vortex::Ref<Vortex::Texture2D> atlasTex = Vortex::Texture2D::Create("Textures/Set_A_Standard_Coast.png", Vortex::TextureFormat::RGBA16);
    atlasTex->MakeHandleResident();

    auto& tile = Vortex::SCENE->CreateObject();
    auto& subSpriteComponent = tile.AddComponent<Vortex::SubSpriteComponent>();

    Vortex::SubSpriteComponent* tiles = new Vortex::SubSpriteComponent[10];

    //for (int i = 0; i < 9; i++)
    //{
     //   auto& tile = Vortex::SCENE->CreateObject();
     //   auto& subSpriteComponent = tile.AddComponent<Vortex::SubSpriteComponent>();

     //   tiles[i] = subSpriteComponent;
    //}

    Vortex::SubSprite::CreateWithCells(tiles[0], atlasTex, { 1, 14 }, { 16, 16 }, {1, 1});
    Vortex::SubSprite::CreateWithCells(tiles[1], atlasTex, { 1, 15 }, { 16, 16 }, {1, 1});
    Vortex::SubSprite::CreateWithCells(tiles[2], atlasTex, { 0, 15 }, { 16, 16 }, {1, 1});
    Vortex::SubSprite::CreateWithCells(tiles[3], atlasTex, { 0, 14 }, { 16, 16 }, {1, 1});
    Vortex::SubSprite::CreateWithCells(tiles[4], atlasTex, { 0, 13 }, { 16, 16 }, {1, 1});
    Vortex::SubSprite::CreateWithCells(tiles[5], atlasTex, { 1, 13 }, { 16, 16 }, {1, 1});
    Vortex::SubSprite::CreateWithCells(tiles[6], atlasTex, { 2, 13 }, { 16, 16 }, {1, 1});
    Vortex::SubSprite::CreateWithCells(tiles[7], atlasTex, { 2, 14 }, { 16, 16 }, {1, 1});
    Vortex::SubSprite::CreateWithCells(tiles[8], atlasTex, { 2, 15 }, { 16, 16 }, {1, 1});
    Vortex::SubSprite::CreateWithCells(tiles[9], atlasTex, { -1, -1 },{ 16, 16 }, {1, 1});

    m_TextureMap.insert({ '0', tiles[0] });
    m_TextureMap.insert({ '1', tiles[1] });
    m_TextureMap.insert({ '3', tiles[2] });
    m_TextureMap.insert({ '2', tiles[3] });
    m_TextureMap.insert({ '6', tiles[4] });
    m_TextureMap.insert({ '4', tiles[5] });
    m_TextureMap.insert({ 'c', tiles[6] });
    m_TextureMap.insert({ '8', tiles[7] });
    m_TextureMap.insert({ '9', tiles[8] });
    m_TextureMap.insert({ ' ', tiles[9] });

    tileMapData.m_TileMap = tileMapStr;
    tileMapData.m_TileDictionary = m_TextureMap;
    tileMapData.m_AtlasTexture = atlasTex;
    tileMapData.m_MapWidth = 20;

    tileMap = Vortex::SCENE->CreateObject();
    auto& transformComponent = tileMap.AddComponent<Vortex::TransformComponent>();
    Vortex::Transform::SetScale(transformComponent, {2.f, 2.f, 2.f});
    auto& spriteComponent = tileMap.AddComponent<Vortex::SpriteComponent>();
    spriteComponent = Vortex::TileMap::GenUnifiedTileMap(tileMapData);
}

void WorldLayer::OnUpdate()
{
    auto& spriteComp = tileMap.GetComponent<Vortex::SpriteComponent>();
    static float delta = 0.f;
    glm::vec4 dawnCol = {0.06f, 0.05f, 0.08f, 1.f};
    glm::vec4 duskCol = {0.8f, 0.8f, 0.8f, 1.f};

    delta += Vortex::Time::GetDeltaTime() * 0.05f;

    spriteComp.m_Tint = glm::mix(duskCol, dawnCol, sinf(delta));
}

void WorldLayer::OnImGuiRender(){
    ImGui::Begin("World");
    ImGui::InputTextMultiline("TileMap", tileMapData.m_TileMap.data(), sizeof(char) * 100 * 100);
    ImGui::InputInt("Map Width", (int*)&tileMapData.m_MapWidth);
    if(ImGui::Button("Generate")){
        auto& sprite = tileMap.GetComponent<Vortex::SpriteComponent>();
        sprite = Vortex::TileMap::GenUnifiedTileMap(tileMapData);
    }
    ImGui::ColorEdit4("Tint", (float*)&tileMap.GetComponent<Vortex::SpriteComponent>().m_Tint);
    ImGui::End();
}
