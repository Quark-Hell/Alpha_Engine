#include "MyScript.h"

#include "Modules.h"


void MyScript::CameraRotate() {
    if (winSettings.win1->GetCursorVisible() == true)
        return;

    double sensitive = 7;
    sensitive *= Core::World::GetDeltaTime();

    Core::SystemData *mouseData = Core::World::GetSystemData("MouseSensorsBuffer");
    auto mouse = reinterpret_cast<BindsEngine::MouseSensors*>(mouseData);

    if (mouse->IsMouseChangePosition()) {

        glm::vec2 delta;
        delta.x = mouse->GetMouseDelta().x;
        delta.y = mouse->GetMouseDelta().y;

        glm::vec3 newRot = Player->transform.GetRotation();

        newRot.x += delta.y * sensitive;
        newRot.y += delta.x * sensitive;

        Player->transform.SetRotation(newRot);

    }
}

void MyScript::LeftMoveCamera() {
    glm::vec3 newPos = Player->transform.GetPosition();

    glm::vec3 UpVector;

    UpVector.x = sinf((Player->transform.GetRotation().y + 90) * 3.14159 / 180);
    UpVector.y = 0;
    UpVector.z = sinf((Player->transform.GetRotation().y) * 3.14159 / 180);

    float sensitive = moveSensitive;
    sensitive *= Core::World::GetDeltaTime();
    newPos += UpVector * sensitive;

    Player->transform.SetPosition(newPos);
}
void MyScript::RightMoveCamera() {
    glm::vec3 newPos = Player->transform.GetPosition();

    glm::vec3 UpVector;

    UpVector.x = sin((Player->transform.GetRotation().y + 90) * 3.14159 / 180);
    UpVector.y = 0;
    UpVector.z = sin((Player->transform.GetRotation().y) * 3.14159 / 180);

    float sensitive = moveSensitive;
    sensitive *= Core::World::GetDeltaTime();
    newPos += UpVector * (-sensitive);

    Player->transform.SetPosition(newPos);
}

void MyScript::ForwardMoveCamera() {
    glm::vec3 newPos = Player->transform.GetPosition();

    glm::vec3 ForwardVector{ 0,0,0 };

    ForwardVector.x = sin((Player->transform.GetRotation().y + 180) * 3.14159 / 180); // RIGHT
    ForwardVector.y = cos((Player->transform.GetRotation().x + 270) * 3.14159 / 180); // RIGHT
    ForwardVector.z = sin((Player->transform.GetRotation().y + 90) * 3.14159 / 180); // RIGHT

    float sensitive = moveSensitive;
    sensitive *= Core::World::GetDeltaTime();
    newPos += ForwardVector * sensitive;

    Player->transform.SetPosition(newPos);
}
void MyScript::BackwardMoveCamera() {
    glm::vec3 newPos = Player->transform.GetPosition();

    glm::vec3 BackwardVector{ 0,0,0 };

    BackwardVector.x = sin((Player->transform.GetRotation().y + 180) * 3.14159 / 180); // RIGHT
    BackwardVector.y = cos((Player->transform.GetRotation().x + 270) * 3.14159 / 180); // RIGHT
    BackwardVector.z = sin((Player->transform.GetRotation().y + 90) * 3.14159 / 180); // RIGHT

    float sensitive = moveSensitive;
    sensitive *= Core::World::GetDeltaTime();
    newPos += BackwardVector * (-sensitive);

    Player->transform.SetPosition(newPos);
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
    auto& obj2 = Core::Factory::CreateObject();
    obj2.SetName("Mesh");
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
    auto& LightsSource = Core::Factory::CreateObject();
    LightsSource.transform.AddPosition(0,5,0);

    auto& dirLight = directLightsBuffer->CreateDirectLight();
    dirLight.Intensity = 0.1;
    LightsSource.AddComponent(dirLight);

    auto& pointLight = pointLightsBuffer->CreatePointLight();
    pointLight.Intensity = 100;
    LightsSource.AddComponent(pointLight);
}

void MyScript::GenerateEarth() {
    auto& cube = Core::Factory::CreateObject();

    cube.transform.AddPosition(0, -5, -25);
    cube.transform.AddRotation(0, 0, 0);
    cube.transform.SetScale(50, 0.5, 50);

    cube.SetName("Cube");

    auto& cubeMesh = meshesBuffer->CreateMesh("/Assets/Models/Primitives/Cube.fbx");
    cube.AddComponent(cubeMesh);

    auto& shader = cubeMesh._material.InitShader<AnomalyEngine::OpaqueShader>();
    shader.LoadTextures(
        "/Assets/Textures/Planets/8k_earth_daymap.jpeg",
        "",
        "",
        "",
        "",
        "/Assets/Textures/Planets/8k_earth_nightmap.jpg");
}

void MyScript::GenerateSun() {
    auto& Sun = Core::Factory::CreateObject();

    Sun.transform.AddPosition(0, 35, -55);
    Sun.transform.SetScale(15, 15, 15);

    Sun.SetName("Sun");

    auto& sunMesh = meshesBuffer->CreateMesh("/Assets/Models/Primitives/Sphere.fbx");
    Sun.AddComponent(sunMesh);

    auto& shader = sunMesh._material.InitShader<AnomalyEngine::SimplexFractalShader>();
    shader.resolution = 3;
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

    Player = &Core::Factory::CreateObject();
    Player->SetName("TestObject");

#if WINDOWS_MANAGER_INCLUDED
    const auto windowsBuffer = Core::World::GetSystemData("WindowsBuffer");
    if (windowsBuffer == nullptr) {
        Core::Logger::LogError("Failed to get windows buffer: " + __LOGERROR__);
        return;
    }
    const auto windows = reinterpret_cast<WindowsManager::WindowsBuffer*>(windowsBuffer);

    winSettings.win1 = windows->CreateWindow(1280, 720, "Windows 1");
    winSettings.win1->SetCursorVisible(false);
#endif

#if BINDS_ENGINE_INCLUDED
    {
        using namespace BindsEngine;

        auto* bindsBuffer = Core::World::GetSystemData("BindsBuffer");
        if (bindsBuffer == nullptr) {
            Core::Logger::LogError("BindsBuffer does not exist: " + __LOGERROR__);
            return;
        }
        auto* buffer = reinterpret_cast<BindsBuffer*>(bindsBuffer);

        /*auto& showCursor =*/ buffer->CreateKeyboardBind(
            { std::bind(&WindowsSettings::ShowCursor, winSettings) },
            { EnumKeyboardKeysStates::KeyPressed },
            { EnumKeyboardTable::LAlt },
            winSettings.win1);

        /*auto& hideCursor =*/ buffer->CreateKeyboardBind(
            { std::bind(&WindowsSettings::HideCursor, winSettings) },
            { EnumKeyboardKeysStates::KeyReleased },
            { EnumKeyboardTable::LAlt },
            winSettings.win1
        );

        /*auto& leftMove =*/ buffer->CreateKeyboardBind(
            { std::bind(&MyScript::LeftMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::A },
            winSettings.win1
        );

        /*auto& rightMove =*/ buffer->CreateKeyboardBind(
            { std::bind(&MyScript::RightMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::D },
            winSettings.win1
        );

        /*auto& forwardMove =*/ buffer->CreateKeyboardBind(
            { std::bind(&MyScript::ForwardMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::W },
            winSettings.win1
        );

        /*auto& backwardMove =*/ buffer->CreateKeyboardBind(
            { std::bind(&MyScript::BackwardMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::S },
            winSettings.win1
        );

        /*auto& upMove =*/ buffer->CreateKeyboardBind(
            { std::bind(&MyScript::UpMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::Q },
            winSettings.win1
        );

        /*auto& downMove =*/ buffer->CreateKeyboardBind(
            { std::bind(&MyScript::DownMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::E },
            winSettings.win1
        );


        /*auto& rotateBind =*/ buffer->CreateMouseSensorBind(
            { std::bind(&MyScript::CameraRotate, this) },
            { EnumMouseSensorStates::MouseKeepMoved, EnumMouseSensorStates::MouseStartMoved },
            winSettings.win1
        );

        buffer->CreateKeyboardBind(
            { std::bind(&MyScript::PushRight, this, std::ref(winSettings.rects)) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::Right },
            winSettings.win1
        );
        buffer->CreateKeyboardBind(
            { std::bind(&MyScript::PushLeft, this, std::ref(winSettings.rects)) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::Left },
            winSettings.win1
        );
        buffer->CreateKeyboardBind(
            { std::bind(&MyScript::PushUp, this, std::ref(winSettings.rects)) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::Up },
            winSettings.win1
        );
        buffer->CreateKeyboardBind(
            { std::bind(&MyScript::PushDown, this, std::ref(winSettings.rects)) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::Down },
            winSettings.win1
        );

        buffer->CreateKeyboardBind(
            { std::bind(&MyScript::ChangeRect, this, std::ref(winSettings.rects)) },
            {EnumKeyboardKeysStates::KeyReleased },
            {EnumKeyboardTable::Add },
            winSettings.win1
        );

        //bind.IsActive = false;
    }
#endif

#if ANOMALY_ENGINE_INCLUDED
    winSettings.WindowsTest5(*Player);

    GenerateCubeMap();
    GenerateEarth();
    GenerateLightSource();
    GenerateSun();
#endif
}
//Call every frame
void MyScript::Update() {
    //Core::Logger::LogInfo(Core::World::GetDeltaTime());
}
//Call before deleted
void MyScript::End() {

}