#include "WorldBuilder.h"

#include "Modules.h"

void WorldBuilder::GenerateLightSource() {
    auto& LightsSource = Core::Factory::CreateObject<Core::GameObject>();
    LightsSource.transform.AddPosition(0, 5, 0);

    auto& dirLight = directLightsBuffer->CreateDirectLight();
    dirLight.Intensity = 0.1;
    LightsSource.AddComponent(dirLight);

    auto& pointLight = pointLightsBuffer->CreatePointLight();
    pointLight.Intensity = 100;
    LightsSource.AddComponent(pointLight);
}

void WorldBuilder::GenerateCubeMap() {
    auto& CubeMap = Core::Factory::CreateObject<Core::GameObject>();
    CubeMap.SetName("CubeMap");

    Core::Geometry& meshGem = Core::Factory::CreateResource<Core::Geometry>();
    meshGem.LoadMesh(GAME_ASSETS_PATH "/Models/Primitives/Cube.fbx", Core::GeometryLoadSettings::All);

    auto& mesh = meshesBuffer->CreateMesh(meshGem);
    CubeMap.AddComponent(mesh);

    auto& shader = mesh._material.InitShader<AnomalyEngine::CubeMapShader>();
    shader.LoadTextures(
        GAME_ASSETS_PATH R"(/Textures/CubeMap/Left_Tex.tga)",
        GAME_ASSETS_PATH R"(/Textures/CubeMap/Right_Tex.tga)",
        GAME_ASSETS_PATH R"(/Textures/CubeMap/Top_Tex.tga)",
        GAME_ASSETS_PATH R"(/Textures/CubeMap/Bottom_Tex.tga)",
        GAME_ASSETS_PATH R"(/Textures/CubeMap/Front_Tex.tga)",
        GAME_ASSETS_PATH R"(/Textures/CubeMap/Back_Tex.tga)"
    );
}

void WorldBuilder::GenerateCube() {
    Core::Geometry& meshGem = Core::Factory::CreateResource<Core::Geometry>();
    meshGem.LoadMesh(GAME_ASSETS_PATH "/Models/Primitives/Cube.fbx", Core::GeometryLoadSettings::All);

    Core::Geometry& colGem = Core::Factory::CreateResource<Core::Geometry>();
    colGem.LoadMesh(GAME_ASSETS_PATH "/Models/Primitives/Cube.fbx", Core::GeometryLoadSettings::InitVertex);

    {
        auto& cube = Core::Factory::CreateObject<Core::GameObject>();

        cube.transform.AddPosition(5, 45, -25);
        cube.transform.AddRotation(0, 0, 0);
        cube.transform.SetScale(1, 1, 1);

        cube.SetName("Cube");

        auto& cubeMesh = meshesBuffer->CreateMesh(meshGem);
        cube.AddComponent(cubeMesh);

        auto& shader = cubeMesh._material.InitShader<AnomalyEngine::OpaqueShader>();
        shader.LoadTextures(
            GAME_ASSETS_PATH "/Textures/Planets/2k_earth_daymap.jpg",
            "",
            "",
            "",
            "",
            GAME_ASSETS_PATH "/Textures/Planets/2k_earth_nightmap.jpg");

        auto& cubeCollider = collidersBuffer->CreateCollider<AxisEngine::CubeCollider>(*physicsSystem);
        cube.AddComponent(cubeCollider);

        auto& cubeRigidBody = rigidBodiesBuffer->CreateRigidBody(*physicsSystem, AxisEngine::RigidBodyType::Dynamic);
        cube.AddComponent(cubeRigidBody);

        SonarEngine::AudioClip& audioClip = Core::Factory::CreateResource<SonarEngine::AudioClip>();
        audioClip.LoadMusic(GAME_ASSETS_PATH "/Audio/Gachi_remix_mono.wav");

        SonarEngine::AudioSource& audioSource = audioSourcesBuffer->CreateAudioSource();
        audioSource.SetAudioClip(audioClip);
        cube.AddComponent(audioSource);
        audioSource.PlayMusic();
    }

    {
        plane = &Core::Factory::CreateObject<Core::GameObject>();

        plane->transform.AddPosition(5, 5, -25);
        plane->transform.AddRotation(30, 0, 0);
        plane->transform.SetScale(15, 1, 15);

        plane->SetName("Plane");

        auto& cubeMesh = meshesBuffer->CreateMesh(meshGem);
        plane->AddComponent(cubeMesh);

        auto& shader = cubeMesh._material.InitShader<AnomalyEngine::OpaqueShader>();
        shader.LoadTextures(
            GAME_ASSETS_PATH "/Textures/Planets/2k_earth_daymap.jpg",
            "",
            "",
            "",
            "",
            GAME_ASSETS_PATH "/Textures/Planets/2k_earth_nightmap.jpg");

        auto& meshCollider = collidersBuffer->CreateCollider<AxisEngine::ConvexMeshCollider>(*physicsSystem);
        meshCollider.LoadGeometry(colGem);
        plane->AddComponent(meshCollider);

        auto& cubeRigidBody = rigidBodiesBuffer->CreateRigidBody(*physicsSystem, AxisEngine::RigidBodyType::Kinematic);
        plane->AddComponent(cubeRigidBody);
    }
}

void WorldBuilder::GenerateEarth() {
    auto& cube = Core::Factory::CreateObject<Core::GameObject>();

    cube.transform.AddPosition(0, -5, -25);
    cube.transform.AddRotation(0, 0, 0);
    cube.transform.SetScale(500, 0.5, 500);

    cube.SetName("Earth");

    Core::Geometry& meshGem = Core::Factory::CreateResource<Core::Geometry>();
    meshGem.LoadMesh(GAME_ASSETS_PATH "/Models/Primitives/Cube.fbx", Core::GeometryLoadSettings::All);

    auto& earthMesh = meshesBuffer->CreateMesh(meshGem);
    earthMesh.LoadMesh(meshGem);

    auto& shader = earthMesh._material.InitShader<AnomalyEngine::OpaqueShader>();
    shader.LoadTextures(
        GAME_ASSETS_PATH "/Textures/Planets/2k_earth_daymap.jpg",
        "",
        "",
        "",
        "",
        GAME_ASSETS_PATH "/Textures/Planets/2k_earth_nightmap.jpg");

    cube.AddComponent(earthMesh);

    Core::Geometry& colliderGem = Core::Factory::CreateResource<Core::Geometry>();
    colliderGem.LoadMesh(GAME_ASSETS_PATH "/Models/Primitives/Cube.fbx", Core::GeometryLoadSettings::InitVertex);
    
    auto& cubeCollider = collidersBuffer->CreateCollider<AxisEngine::CubeCollider>(*physicsSystem);
    cube.AddComponent(cubeCollider);

    auto& cubeRigidBody = rigidBodiesBuffer->CreateRigidBody(*physicsSystem, AxisEngine::RigidBodyType::Kinematic);
    cube.AddComponent(cubeRigidBody);
}

void WorldBuilder::GenerateSun() {
    auto& Sun = Core::Factory::CreateObject<Core::GameObject>();

    Sun.transform.AddPosition(0, 55, -55);
    Sun.transform.SetScale(35, 35, 35);

    Sun.SetName("Sun");

    Core::Geometry& geometry = Core::Factory::CreateResource<Core::Geometry>();
    geometry.LoadMesh("/Assets/Models/Sci-Fi_Football.fbx", Core::GeometryLoadSettings::All);

    auto& sunMesh = meshesBuffer->CreateMesh(geometry);

    Sun.AddComponent(sunMesh);

    auto& shader = sunMesh._material.InitShader<AnomalyEngine::SimplexFractalShader>();

    Core::Geometry& collider = Core::Factory::CreateResource<Core::Geometry>();
    collider.LoadMesh("/Assets/Models/Sci-Fi_Football.fbx", Core::GeometryLoadSettings::InitVertex);

    shader.Contrast = 6.4;
    shader.Brightness = 0.15;
}


void WorldBuilder::Start() {
#if ANOMALY_ENGINE_INCLUDED
    GenerateCubeMap();
    GenerateEarth();
    GenerateLightSource();
    //GenerateSun();
    GenerateCube();
#endif
}

void WorldBuilder::Update() {
    //plane->transform.AddPosition(0, 0, -0.1);
    plane->transform.AddRotation(1, 0, 0);
    //plane->transform.AddScale(0, 0, 0.1);
}

void WorldBuilder::End() {

}