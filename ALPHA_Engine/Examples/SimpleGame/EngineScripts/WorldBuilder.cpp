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
    meshGem.LoadMesh("/Assets/Models/Primitives/Cube.fbx", Core::GeometryLoadSettings::All);

    auto& mesh = meshesBuffer->CreateMesh(meshGem);
    CubeMap.AddComponent(mesh);

    auto& shader = mesh._material.InitShader<AnomalyEngine::CubeMapShader>();
    shader.LoadTextures(
        R"(/Assets/Textures/CubeMap/Left_Tex.tga)",
        R"(/Assets/Textures/CubeMap/Right_Tex.tga)",
        R"(/Assets/Textures/CubeMap/Top_Tex.tga)",
        R"(/Assets/Textures/CubeMap/Bottom_Tex.tga)",
        R"(/Assets/Textures/CubeMap/Front_Tex.tga)",
        R"(/Assets/Textures/CubeMap/Back_Tex.tga)"
    );
}

void WorldBuilder::GenerateCube() {
    Core::Geometry& meshGem = Core::Factory::CreateResource<Core::Geometry>();
    meshGem.LoadMesh("/Assets/Models/Primitives/Cube.fbx", Core::GeometryLoadSettings::All);

    Core::Geometry& colGem = Core::Factory::CreateResource<Core::Geometry>();
    colGem.LoadMesh("/Assets/Models/Primitives/Cube.fbx", Core::GeometryLoadSettings::InitVertex);

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
            "/Assets/Textures/Planets/8k_earth_daymap.jpeg",
            "",
            "",
            "",
            "",
            "/Assets/Textures/Planets/8k_earth_nightmap.jpg");

        auto& cubeCollider = collidersBuffer->CreateCollider<AxisEngine::MeshCollider>();
        cubeCollider.Create(colGem);
        cube.AddComponent(cubeCollider);

        auto& cubeRigidBody = rigidBodiesBuffer->CreateRigidBody();
        cube.AddComponent(cubeRigidBody);
    }

    {
        auto& cube = Core::Factory::CreateObject<Core::GameObject>();

        cube.transform.AddPosition(5, 5, -25);
        cube.transform.AddRotation(30, 0, 0);
        cube.transform.SetScale(15, 1, 15);

        cube.SetName("Plane");

        auto& cubeMesh = meshesBuffer->CreateMesh(meshGem);
        cube.AddComponent(cubeMesh);

        auto& shader = cubeMesh._material.InitShader<AnomalyEngine::OpaqueShader>();
        shader.LoadTextures(
            "/Assets/Textures/Planets/8k_earth_daymap.jpeg",
            "",
            "",
            "",
            "",
            "/Assets/Textures/Planets/8k_earth_nightmap.jpg");

        auto& cubeCollider = collidersBuffer->CreateCollider<AxisEngine::MeshCollider>();
        cubeCollider.Create(colGem);
        cube.AddComponent(cubeCollider);
    }


}

void WorldBuilder::GenerateEarth() {
    auto& cube = Core::Factory::CreateObject<Core::GameObject>();

    cube.transform.AddPosition(0, -5, -25);
    cube.transform.AddRotation(0, 0, 0);
    cube.transform.SetScale(50, 0.5, 50);

    cube.SetName("Earth");

    Core::Geometry& meshGem = Core::Factory::CreateResource<Core::Geometry>();
    meshGem.LoadMesh("/Assets/Models/Primitives/Cube.fbx", Core::GeometryLoadSettings::All);

    auto& earthMesh = meshesBuffer->CreateMesh(meshGem);
    earthMesh.LoadMesh(meshGem);

    auto& shader = earthMesh._material.InitShader<AnomalyEngine::OpaqueShader>();
    shader.LoadTextures(
        "/Assets/Textures/Planets/8k_earth_daymap.jpeg",
        "",
        "",
        "",
        "",
        "/Assets/Textures/Planets/8k_earth_nightmap.jpg");

    cube.AddComponent(earthMesh);

    Core::Geometry& colliderGem = Core::Factory::CreateResource<Core::Geometry>();
    colliderGem.LoadMesh("/Assets/Models/Primitives/Cube.fbx", Core::GeometryLoadSettings::InitVertex);
    
    auto& cubeCollider = collidersBuffer->CreateCollider<AxisEngine::MeshCollider>();
    cubeCollider.Create(colliderGem);
    cube.AddComponent(cubeCollider);
}

void WorldBuilder::GenerateSun() {
    auto& Sun = Core::Factory::CreateObject<Core::GameObject>();

    Sun.transform.AddPosition(0, 55, -55);
    Sun.transform.SetScale(35, 35, 35);

    Sun.SetName("Sun");

    Core::Geometry& geometry = Core::Factory::CreateResource<Core::Geometry>();
    geometry.LoadMesh("/Assets/Models/Sci-Fi_Football.fbx", Core::GeometryLoadSettings::All);

    auto& sunMesh = meshesBuffer->CreateMesh(geometry);
    auto& rb = rigidBodiesBuffer->CreateRigidBody();

    Sun.AddComponent(sunMesh);
    Sun.AddComponent(rb);

    auto& shader = sunMesh._material.InitShader<AnomalyEngine::SimplexFractalShader>();

    Core::Geometry& collider = Core::Factory::CreateResource<Core::Geometry>();
    collider.LoadMesh("/Assets/Models/Sci-Fi_Football.fbx", Core::GeometryLoadSettings::InitVertex);

    auto& cubeCollider = collidersBuffer->CreateCollider<AxisEngine::MeshCollider>();
    cubeCollider.Create(collider);
    Sun.AddComponent(cubeCollider);

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

}

void WorldBuilder::End() {

}