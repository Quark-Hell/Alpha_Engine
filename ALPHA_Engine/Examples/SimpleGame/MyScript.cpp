#include "MyScript.h"

#include "Modules.h"


void MyScript::CameraRotate() {
    if (winSettings.win1->GetCursorVisible() == true)
        return;

    auto mouseData = Core::World::GetSystemData<BindsEngine::MouseSensors>("MouseSensorsBuffer");

    float sensitive = 0.15;
    glm::vec2 delta = mouseData->GetMouseDelta();

    static float targetYaw = 0.0f;
    static float targetPitch = 0.0f;

    targetYaw   += delta.x * sensitive;
    targetPitch += delta.y * sensitive;

    targetPitch = glm::clamp(targetPitch, -89.0f, 89.0f);

    glm::quat qYaw = glm::angleAxis(glm::radians(targetYaw), glm::vec3(0, 1, 0));
    glm::quat qPitch = glm::angleAxis(glm::radians(targetPitch), glm::vec3(1, 0, 0));

    glm::quat targetRot = qPitch * qYaw;

    float slerpSpeed = 10.0f * Core::World::GetDeltaTime();
    slerpSpeed = glm::clamp(slerpSpeed, 0.0f, 1.0f);

    Player->transform.SetRotationQuatSlerp(targetRot, slerpSpeed);
}

void MyScript::LeftMoveCamera() {
    glm::vec3 rightVector = Player->transform.GetRight();
    float sensitive = moveSensitive * Core::World::GetDeltaTime();

    Player->transform.AddPosition(rightVector * sensitive);
}

void MyScript::RightMoveCamera() {
    glm::vec3 rightVector = Player->transform.GetRight();
    float sensitive = moveSensitive * Core::World::GetDeltaTime();

    Player->transform.AddPosition(-rightVector * sensitive);
}

void MyScript::ForwardMoveCamera() {
    glm::vec3 forwardVector = Player->transform.GetForward();
    float sensitive = moveSensitive * Core::World::GetDeltaTime();

    Player->transform.AddPosition(forwardVector * sensitive);
}

void MyScript::BackwardMoveCamera() {
    glm::vec3 forwardVector = Player->transform.GetForward();
    float sensitive = moveSensitive * Core::World::GetDeltaTime();

    Player->transform.AddPosition(-forwardVector * sensitive);
}

void MyScript::UpMoveCamera() {
    glm::vec3 newPos = Player->transform.GetPosition();

    float sensitive = moveSensitive;
    sensitive *= Core::World::GetDeltaTime();
    newPos.y += sensitive;

    Player->transform.SetPosition(newPos);
}
void MyScript::DownMoveCamera() {
    glm::vec3 newPos = Player->transform.GetPosition();

    float sensitive = moveSensitive;
    sensitive *= Core::World::GetDeltaTime();
    newPos.y -= sensitive;

    Player->transform.SetPosition(newPos);
}


void MyScript::PushUp(std::vector<WindowsManager::Rectangle*>& rectBuffer) {
    float delta = 0.2f;
    delta *= Core::World::GetDeltaTime();

    {
        Core::ScopedTimer timer("timer");
        //winSettings.win1->PushTopRectEdge(delta, *winSettings.rect);
        winSettings.win1->PushBottomRectEdge(-delta, *rectBuffer[CurrentRectID]);
    }
}
void MyScript::PushDown(std::vector<WindowsManager::Rectangle*>& rectBuffer) {
    float delta = -0.2f;
    delta *= Core::World::GetDeltaTime();

    {
        Core::ScopedTimer timer("timer");
        //winSettings.win1->PushTopRectEdge(delta, *winSettings.rect);
        winSettings.win1->PushBottomRectEdge(-delta, *rectBuffer[CurrentRectID]);
    }
}

void MyScript::PushRight(std::vector<WindowsManager::Rectangle*>& rectBuffer) {
    float delta = -0.2f;
    delta *= Core::World::GetDeltaTime();

    {
        Core::ScopedTimer timer("timer");
        winSettings.win1->PushRightRectEdge(-delta, *rectBuffer[CurrentRectID]);  // -->
    }
    //win1->PushLeftRectEdge(delta, *rect);  // -->
}
void MyScript::PushLeft(std::vector<WindowsManager::Rectangle*>& rectBuffer) {
    if(CurrentRectID == 6) { return; }

    float delta = 0.2f;
    delta *= Core::World::GetDeltaTime();

    winSettings.win1->PushRightRectEdge(-delta, *rectBuffer[CurrentRectID]); // <--
    //win1->PushLeftRectEdge(delta, *rect);  // -->
}

void MyScript::ChangeRect(std::vector<WindowsManager::Rectangle*>& rectBuffer) {
    if (CurrentRectID + 1 >= rectBuffer.size()) {
        CurrentRectID = 0;
        return;
    }

    CurrentRectID++;
}

void MyScript::GenerateCubeMap() {
    auto& obj2 = Core::Factory::CreateObject<Core::GameObject>();
    obj2.SetName("CubeMap");
    auto& mesh = meshesBuffer->CreateMesh("/Assets/Models/Primitives/Cube.fbx");
    obj2.AddComponent(mesh);

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

void MyScript::GenerateLightSource() {
    auto& LightsSource = Core::Factory::CreateObject<Core::GameObject>();
    LightsSource.transform.AddPosition(0,5,0);

    auto& dirLight = directLightsBuffer->CreateDirectLight();
    dirLight.Intensity = 0.1;
    LightsSource.AddComponent(dirLight);

    auto& pointLight = pointLightsBuffer->CreatePointLight();
    pointLight.Intensity = 100;
    LightsSource.AddComponent(pointLight);
}

void MyScript::GenerateCube() {
    {
        auto& cube = Core::Factory::CreateObject<Core::GameObject>();

        cube.transform.AddPosition(5, 45, -25);
        cube.transform.AddRotation(0, 0, 0);
        cube.transform.SetScale(1, 1, 1);

        cube.SetName("Cube");

        cube.AddComponent(*cubeMesh);

        auto& cubeRigidBody = rigidBodiesBuffer->CreateRigidBody();
        cube.AddComponent(cubeRigidBody);
        
        auto& cubeCollider = collidersBuffer->CreateCollider<AxisEngine::MeshCollider>();
        cubeCollider.Create("/Assets/Models/Primitives/Cube.fbx");
        cube.AddComponent(cubeCollider);
    }

    {
        auto& cube = Core::Factory::CreateObject<Core::GameObject>();

        cube.transform.AddPosition(5, 5, -25);
        cube.transform.AddRotation(30, 0, 0);
        cube.transform.SetScale(15, 1, 15);

        cube.SetName("Plane");

        cube.AddComponent(*cubeMesh);

        auto& cubeCollider = collidersBuffer->CreateCollider<AxisEngine::MeshCollider>();
        cubeCollider.Create("/Assets/Models/Primitives/Cube.fbx");
        cube.AddComponent(cubeCollider);
    }


}

void MyScript::GenerateEarth() {
    auto& cube = Core::Factory::CreateObject<Core::GameObject>();

    cube.transform.AddPosition(0, -5, -25);
    cube.transform.AddRotation(0, 0, 0);
    cube.transform.SetScale(50, 0.5, 50);

    cube.SetName("Cube");

    cube.AddComponent(*cubeMesh);

    auto& cubeCollider = collidersBuffer->CreateCollider<AxisEngine::MeshCollider>();
    cubeCollider.Create("/Assets/Models/Primitives/Cube.fbx");
    cube.AddComponent(cubeCollider);
}

void MyScript::GenerateSun() {
    auto& Sun = Core::Factory::CreateObject<Core::GameObject>();

    Sun.transform.AddPosition(0, 35, -55);
    Sun.transform.SetScale(15, 15, 15);

    Sun.SetName("Sun");

    auto& sunMesh = meshesBuffer->CreateMesh("/Assets/Models/Primitives/Sphere.fbx");
    Sun.AddComponent(sunMesh);

    auto& shader = sunMesh._material.InitShader<AnomalyEngine::SimplexFractalShader>();

    shader.Contrast = 6.4;
    shader.Brightness = 0.15;
}

void MyScript::Serialization() {
    DerivedData data{10,20,30,40};
    DerivedData res{0,0,0,0};

    Core::TSerialized<DerivedData> dataBuffer;
    dataBuffer.Serialize(data);
    dataBuffer.Deserialize(res);

    Core::TSerialized<DerivedData>::SaveData(data,"/Saved.bin");
    Core::TSerialized<DerivedData>::LoadData(data,"/Saved.bin");
}
void MyScript::LogExample() {
#if LOGGER_INCLUDED
    Core::Logger::LogInfo("TestLoggerEvent");
    Core::Logger::LogWarning("TestLoggerWarning");
    Core::Logger::LogError("TestLoggerError: " + __LOGERROR__);
    //Logger::Logger::LogCritical("TestLoggerCritical: " + __LOGERROR__); //This crash Game with your error
#endif
}

//Call after created
void MyScript::Start() {
    Serialization();
    LogExample();

    Player = &Core::Factory::CreateObject<Core::GameObject>();
    Player->SetName("TestObject");

#if WINDOWS_MANAGER_INCLUDED
    const auto windowsBuffer = Core::World::GetSystemData<WindowsManager::WindowsBuffer>("WindowsBuffer");
    if (windowsBuffer == nullptr) {
        Core::Logger::LogError("Failed to get windows buffer: " + __LOGERROR__);
        return;
    }

    winSettings.win1 = windowsBuffer->CreateWindow(1280, 720, "Windows 1");
    winSettings.win1->SetCursorVisible(false);
#endif

#if BINDS_ENGINE_INCLUDED
    {
        using namespace BindsEngine;

        auto* bindsBuffer = Core::World::GetSystemData<BindsBuffer>("BindsBuffer");
        if (bindsBuffer == nullptr) {
            Core::Logger::LogError("BindsBuffer does not exist: " + __LOGERROR__);
            return;
        }

        /*auto& showCursor =*/ bindsBuffer->CreateKeyboardBind(
            { std::bind(&WindowsSettings::ShowCursor, winSettings) },
            { EnumKeyboardKeysStates::KeyPressed },
            { EnumKeyboardTable::LAlt },
            winSettings.win1);

        /*auto& hideCursor =*/ bindsBuffer->CreateKeyboardBind(
            { std::bind(&WindowsSettings::HideCursor, winSettings) },
            { EnumKeyboardKeysStates::KeyReleased },
            { EnumKeyboardTable::LAlt },
            winSettings.win1
        );

        /*auto& leftMove =*/ bindsBuffer->CreateKeyboardBind(
            { std::bind(&MyScript::LeftMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::A },
            winSettings.win1
        );

        /*auto& rightMove =*/ bindsBuffer->CreateKeyboardBind(
            { std::bind(&MyScript::RightMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::D },
            winSettings.win1
        );

        /*auto& forwardMove =*/ bindsBuffer->CreateKeyboardBind(
            { std::bind(&MyScript::ForwardMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::W },
            winSettings.win1
        );

        /*auto& backwardMove =*/ bindsBuffer->CreateKeyboardBind(
            { std::bind(&MyScript::BackwardMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::S },
            winSettings.win1
        );

        /*auto& upMove =*/ bindsBuffer->CreateKeyboardBind(
            { std::bind(&MyScript::UpMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::Q },
            winSettings.win1
        );

        /*auto& downMove =*/ bindsBuffer->CreateKeyboardBind(
            { std::bind(&MyScript::DownMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::E },
            winSettings.win1
        );


        /*auto& rotateBind =*/ bindsBuffer->CreateMouseSensorBind(
            { std::bind(&MyScript::CameraRotate, this) },
            { EnumMouseSensorStates::MouseKeepMoved, EnumMouseSensorStates::MouseStartMoved },
            winSettings.win1
        );

        bindsBuffer->CreateKeyboardBind(
            { std::bind(&MyScript::PushRight, this, std::ref(winSettings.rects)) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::Right },
            winSettings.win1
        );
        bindsBuffer->CreateKeyboardBind(
            { std::bind(&MyScript::PushLeft, this, std::ref(winSettings.rects)) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::Left },
            winSettings.win1
        );
        bindsBuffer->CreateKeyboardBind(
            { std::bind(&MyScript::PushUp, this, std::ref(winSettings.rects)) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::Up },
            winSettings.win1
        );
        bindsBuffer->CreateKeyboardBind(
            { std::bind(&MyScript::PushDown, this, std::ref(winSettings.rects)) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::Down },
            winSettings.win1
        );

        bindsBuffer->CreateKeyboardBind(
            { std::bind(&MyScript::ChangeRect, this, std::ref(winSettings.rects)) },
            {EnumKeyboardKeysStates::KeyReleased },
            {EnumKeyboardTable::Add },
            winSettings.win1
        );

        //bind.IsActive = false;
    }
#endif

#if ANOMALY_ENGINE_INCLUDED
    winSettings.BaseWindow(*Player);

    GenerateCubeMap();

    cubeMesh = &meshesBuffer->CreateMesh("/Assets/Models/Primitives/Cube.fbx");
    auto& shader = cubeMesh->_material.InitShader<AnomalyEngine::OpaqueShader>();
    shader.LoadTextures(
        "/Assets/Textures/Planets/8k_earth_daymap.jpeg",
        "",
        "",
        "",
        "",
        "/Assets/Textures/Planets/8k_earth_nightmap.jpg");

    GenerateEarth();
    GenerateLightSource();
    GenerateSun();
    GenerateCube();
#endif
}
//Call every frame
void MyScript::Update() {
    //Core::Logger::LogInfo(Core::World::GetDeltaTime());
}
//Call before deleted
void MyScript::End() {

}