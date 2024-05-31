#include "WorldLayer.h"
#include "Environment/ComponentModifiers.h"
#include "Environment/Components.h"
#include "Jobs/JobScheduler.h"

Vortex::JobData<uint32_t*> CalculateMandelbrot(uint32_t maxiteration, float zoom, glm::vec2 xs, glm::vec2 ys, glm::vec2 offset)
{
    double xrange_start = -2.0f / zoom;
    double xrange_end = 1.0f / zoom;
    double yrange_start = -1.0f / zoom;
    double yrange_end = 1.0f / zoom;

    uint32_t xsize = xs.y - xs.x + 1;
    uint32_t ysize = ys.y - ys.x + 1;
    
    double xslope = 1.0f * (xrange_end - xrange_start) / (xsize);
    double yslope = 1.0f * (yrange_end - yrange_start) / (ysize);

    uint32_t* texData = new uint32_t[xsize * ysize];

    for (uint32_t y = ys.x; y < ys.y + 1; y++)
    {
        for (uint32_t x = xs.x; x < xs.y + 1; x++)
        {
            double x1 = 0.0;
            double y1 = 0.0;

            double x0 = xrange_start + xslope * x - offset.x; //0.52f;
            double y0 = yrange_start + yslope * y - offset.y; //0.6f;

            double x2 = 0.0;
            double y2 = 0.0;

            uint32_t iteration = 0;
            while (x2 + y2 <= 4 && iteration < maxiteration) {
                y1 = 2 * x1 * y1 + y0;
                x1 = x2 - y2 + x0;
                x2 = x1 * x1;
                y2 = y1 * y1;
                iteration++;
            }

            Vortex::RNG::m_Seed = maxiteration - iteration;
            //VORTEX_APP_INFO("texData[{0}] (x: {1}, y: {2}, xsize: {3})", uint32_t(x - xs.x) + uint32_t(y - ys.x) * xsize, uint32_t(x - xs.x), uint32_t(y - ys.x), xsize );
            texData[uint32_t(x - xs.x) + uint32_t(y - ys.x) * xsize] = 0xff000000 * Vortex::RNG::RandFloat() + 0x00ff0000 * Vortex::RNG::RandFloat() + 0x0000ff00 * Vortex::RNG::RandFloat() + 0x000000ff;//m_Pallete[iteration];
            co_yield texData;
        }
    }
    //co_yield texData;

    /*for(uint32_t i = 1; i < 1000; i++) {
        VORTEX_APP_INFO("Printing i: {0}", i);
        co_yield &i;
    }*/
    while(true) { co_yield texData; }
    VORTEX_APP_INFO("Job DONE");
    co_return texData;
}

WorldLayer::WorldLayer() : Layer("WorldLayer")
{
    const uint32_t width = 1024;
    const uint32_t maxiteration = 1000;

    //m_FractalQuad = Vortex::SCENE->CreateObject();
    //auto& transform = m_FractalQuad.AddComponent<Vortex::TransformComponent>();
    //Vortex::Transform::Scale(transform, {100.f, 100.f, 1.f});
    //auto& sprite = m_FractalQuad.AddComponent<Vortex::SpriteComponent>();
    //sprite.m_Texture = Vortex::Texture2D::Create(width, width);
   
    //uint32_t devidedSizeX = width / 8;

    //for(size_t i = 0; i < 8; i++) {
    //    m_MandelbrotJobs[i] = CalculateMandelbrot(maxiteration, 10.f, {devidedSizeX * i, devidedSizeX * (i + 1) - 1}, {0, width}, {-0.52f, -0.6f});
    //    Vortex::JobScheduler::PushJob(m_MandelbrotJobs[i]);
        //VORTEX_APP_INFO("Pushing Job[{0}] with xrange: {1} - {2} and yrange: {3} - {4}", y * 2 + x, devidedSizeX * x, devidedSizeX * (x + 1) - 1, devidedSizeY * y, devidedSizeY * (y + 1) - 1);
    //}

    //m_CombinedMandelbrotTex = new uint32_t[width * width];
    float radius = 15.f;
    uint32_t count = 16;

    auto texture = Vortex::Texture2D::Create("Textures/Ball.png", Vortex::TextureFormat::RGBA8);

    for (size_t x = 0; x < count; x++)
    {
        for (size_t y = 0; y < count; y++)
        {
            Vortex::Object obj = Vortex::SCENE->CreateObject();
            //obj.AddComponent<Vortex::TagComponent>("Ball");
            Vortex::TransformComponent& transform = obj.AddComponent<Vortex::TransformComponent>();
            float angleX = ((360.f / (count)) * x);
            float angleY = ((360.f / (count)) * y);
            Vortex::Transform::SetPosition(transform, { radius * cosf(angleX) * sinf(angleY) + 0.001f * x,
                                                        radius * sinf(angleX) * sinf(angleY) + 0.001f * y,
                                                        radius * cosf(angleY) + 0.0001f * y * x });
            Vortex::Transform::Scale(transform, Vortex::Time::GetDeltaTime() * Vortex::RNG::RandFloat() * glm::vec3(1.f));
            auto& renderer2DComponent = obj.AddComponent<Vortex::SpriteComponent>();
            renderer2DComponent.m_Texture = texture;

            renderer2DComponent.m_Tint = { Vortex::RNG::RandFloat(), Vortex::RNG::RandFloat(), Vortex::RNG::RandFloat(), 1.f };
        }
    }

    ship = Vortex::SCENE->CreateObject();
    auto& transform = ship.AddComponent<Vortex::TransformComponent>();
    Vortex::Transform::SetScale(transform, {1.f, 1.f, 1.f});
    auto& staticMesh = ship.AddComponent<Vortex::StaticMeshComponent>();
    
    Vortex::MeshData meshData;
    Vortex::Mesh::LoadMeshData(meshData, "Models/Ship0.fbx");
    
    Vortex::MaterialData materialData;
    materialData.m_Shader = Vortex::Shader::Create("Shaders/unlitShader.glsl");
    materialData.m_Texture = Vortex::Texture2D::Create("Textures/Ship0.png", Vortex::TextureFormat::RGBA16, Vortex::TextureWrap::REPEAT, Vortex::TextureFilter::NEAREST);
    
    staticMesh.mesh = meshData;
    staticMesh.material = materialData;

    Vortex::FramebufferParams fbParams;
    fbParams.Width = Vortex::App::Get().GetWindow().GetWindowWidth();
    fbParams.Height = Vortex::App::Get().GetWindow().GetWindowHeight();
    m_Framebuffer = Vortex::Framebuffer::Create(fbParams);

}

void WorldLayer::OnUpdate()
{
    auto& staticMesh = ship.GetComponent<Vortex::StaticMeshComponent>();
    staticMesh.IsVisible = false; 
    auto camera = Vortex::SCENE->GetObjectWithComponents<Vortex::CameraComponent>();
    
    Vortex::Renderer2D::BeginScene(camera.GetComponent<Vortex::CameraComponent>(), camera.GetComponent<Vortex::TransformComponent>());
    Vortex::RenderCommand::Clear(); //{204.f / 255.f, 51.f / 255.f, 0.f, 1.f}

    Vortex::SCENE->Update(camera.GetComponent<Vortex::TransformComponent>().m_Position, Vortex::Time::GetDeltaTime());

    Vortex::Renderer2D::EndSceneAndRenderToFramebuffer(m_Framebuffer);
    staticMesh.material.m_Texture = Vortex::Texture2D::Create(m_Framebuffer->GetColorAttachmentID());
    staticMesh.IsVisible = true;
}

void WorldLayer::OnImGuiRender(){
    ImGui::Begin("World");

    ImGui::End();
}
