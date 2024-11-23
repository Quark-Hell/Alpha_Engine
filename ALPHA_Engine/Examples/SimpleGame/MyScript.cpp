#include "MyScript.h"

//===================Core===================//
#include "Core/World.h"
#include "Core/Object.h"
#include "Core/Factory.h"

#include "Core/Logger/Logger.h"
//===================Core===================//

#include "UserScriptsRegister/UserScriptConfig.h"
#include "WindowsManager/WindowsManagerConfig.h"
#include "BindsEngine/BindsEngineConfig.h"

//===================Anomaly Engine===================//
#include "AnomalyEngine/RenderEngine.h"

#include "AnomalyEngine/Buffers/CamerasBuffer.h"
#include "AnomalyEngine/Buffers/MeshesBuffer.h"
#include "AnomalyEngine/Buffers/DirectLightsBuffer.h"
#include "AnomalyEngine/Buffers/PointLightsBuffer.h"

#include "AnomalyEngine/Components/Mesh.h"
#include "AnomalyEngine/Components/Camera.h"
#include "AnomalyEngine/Components/DirectLight.h"
#include "AnomalyEngine/Components/PointLight.h"

#include "AnomalyEngine/Shaders/CubeMapShader.h"
#include "AnomalyEngine/Shaders/OpaqueShader.h"
//===================Anomaly Engine===================//

//===================User Scripts Register===================//
Register::Registry* userScriptSystem;
Register::UserScriptsBuffer* userScriptsBuffer;
//===================User Scripts Register===================//

//===================Binds Engine===================//
BindsEngine::KeyboardSystem* keyboardSystem;
BindsEngine::KeyboardSensors* keyboardBuffer;

BindsEngine::MouseSystem* mouseSystem;
BindsEngine::MouseSensors* mouseBuffer;

BindsEngine::InputSystem* inputSystem;
BindsEngine::BindsBuffer* bindsBuffer;
//===================Binds Engine===================//

//===================Windows Manager===================//
WindowsManager::WindowsManager* windowsSystem;
WindowsManager::WindowsBuffer* windowsBuffer;
//===================Windows Manager===================//

//===================Anomaly Engine===================//
AnomalyEngine::RenderEngine* anomalySystem;
AnomalyEngine::MeshesBuffer* meshesBuffer;
AnomalyEngine::CamerasBuffer* camerasBuffer;
AnomalyEngine::DirectLightsBuffer* directLightsBuffer;
AnomalyEngine::PointLightsBuffer* pointLightsBuffer;
//===================Anomaly Engine===================//

namespace Core {
    //This function will be invoked before general cycle
    //Use this for initialize global data
    void InstanceModule() {
        userScriptSystem = new Register::Registry();
        userScriptsBuffer = new Register::UserScriptsBuffer();

        keyboardSystem = new BindsEngine::KeyboardSystem();
        keyboardBuffer = new BindsEngine::KeyboardSensors();

        mouseSystem = new BindsEngine::MouseSystem();
        mouseBuffer = new BindsEngine::MouseSensors();

        inputSystem = new BindsEngine::InputSystem();
        bindsBuffer = new BindsEngine::BindsBuffer();

        windowsSystem = new WindowsManager::WindowsManager();
        windowsBuffer = new WindowsManager::WindowsBuffer();

        anomalySystem = new AnomalyEngine::RenderEngine();
        meshesBuffer = new AnomalyEngine::MeshesBuffer();
        camerasBuffer = new AnomalyEngine::CamerasBuffer();
        directLightsBuffer = new AnomalyEngine::DirectLightsBuffer();
        pointLightsBuffer = new AnomalyEngine::PointLightsBuffer();

        auto* script = userScriptsBuffer->CreateActor<MyScript>();
    }
}

void MyScript::CameraRotate() {
    if (win1->GetCursorVisible() == true)
        return;

    double sensitive = 7;
    sensitive *= Core::World::GetDeltaTime();

    Core::SystemData *mouseData = Core::World::GetSystemData("MouseSensorsBuffer");
    if (mouseData == nullptr) {

    }
    auto mouse = reinterpret_cast<BindsEngine::MouseSensors*>(mouseData);

    if (mouse->IsMouseChangePosition()) {

        Core::Vector3 delta;
        delta.X = mouse->GetMouseDelta().X;
        delta.Y = mouse->GetMouseDelta().Y;

        auto newRot = static_cast<Core::Vector3>(Player->transform.GetRotation());

        newRot.X += delta.Y * sensitive;
        newRot.Y += delta.X * sensitive;

        Player->transform.SetRotation(newRot);

    }
}

void MyScript::ShowCursor() {
    std::cout << "Show";
    win1->SetCursorVisible(true);
}

void MyScript::HideCursor() {
    win1->SetCursorVisible(false);
}

void MyScript::LeftMoveCamera() {
    Core::Vector3 newPos = Player->transform.GetPosition();

    Core::Vector3 UpVector;

    UpVector.X = sinf((Player->transform.GetRotation().Y + 90) * 3.14159 / 180);
    UpVector.Y = 0;
    UpVector.Z = sinf((Player->transform.GetRotation().Y) * 3.14159 / 180);

    float sensitive = moveSensitive;
    sensitive *= Core::World::GetDeltaTime();
    newPos += UpVector * sensitive;

    Player->transform.SetPosition(newPos);
}

void MyScript::RightMoveCamera() {
    Core::Vector3 newPos = Player->transform.GetPosition();

    Core::Vector3 UpVector;

    UpVector.X = sin((Player->transform.GetRotation().Y + 90) * 3.14159 / 180);
    UpVector.Y = 0;
    UpVector.Z = sin((Player->transform.GetRotation().Y) * 3.14159 / 180);

    float sensitive = moveSensitive;
    sensitive *= Core::World::GetDeltaTime();
    newPos += UpVector * (-sensitive);

    Player->transform.SetPosition(newPos);
}
void MyScript::ForwardMoveCamera() {
    Core::Vector3 newPos = Player->transform.GetPosition();

    Core::Vector3 ForwardVector{ 0,0,0 };

    ForwardVector.X = sin((Player->transform.GetRotation().Y + 180) * 3.14159 / 180); // RIGHT
    ForwardVector.Y = cos((Player->transform.GetRotation().X + 270) * 3.14159 / 180); // RIGHT
    ForwardVector.Z = sin((Player->transform.GetRotation().Y + 90) * 3.14159 / 180); // RIGHT

    float sensitive = moveSensitive;
    sensitive *= Core::World::GetDeltaTime();
    newPos += ForwardVector * sensitive;

    Player->transform.SetPosition(newPos);
}
void MyScript::BackwardMoveCamera() {
    Core::Vector3 newPos = Player->transform.GetPosition();

    Core::Vector3 BackwardVector{ 0,0,0 };

    BackwardVector.X = sin((Player->transform.GetRotation().Y + 180) * 3.14159 / 180); // RIGHT
    BackwardVector.Y = cos((Player->transform.GetRotation().X + 270) * 3.14159 / 180); // RIGHT
    BackwardVector.Z = sin((Player->transform.GetRotation().Y + 90) * 3.14159 / 180); // RIGHT

    float sensitive = moveSensitive;
    sensitive *= Core::World::GetDeltaTime();
    newPos += BackwardVector * (-sensitive);

    Player->transform.SetPosition(newPos);
}

void MyScript::UpMoveCamera() {
    Core::Vector3 newPos = Player->transform.GetPosition();

    float sensitive = moveSensitive;
    sensitive *= Core::World::GetDeltaTime();
    newPos.Y += sensitive;

    Player->transform.SetPosition(newPos);
}
void MyScript::DownMoveCamera() {
    Core::Vector3 newPos = Player->transform.GetPosition();

    float sensitive = moveSensitive;
    sensitive *= Core::World::GetDeltaTime();
    newPos.Y -= sensitive;

    Player->transform.SetPosition(newPos);
}

//Call after created
void MyScript::Start() {
#if LOGGER_INCLUDED
    Core::Logger::LogInfo("TestLoggerEvent");
    Core::Logger::LogWarning("TestLoggerWarning");
    Core::Logger::LogError("TestLoggerError: " + std::string(__FILE__ ":") + std::to_string(__LINE__));
    //Logger::Logger::LogCritical("TestLoggerCritical: " + std::string(__FILE__ ":") + std::to_string(__LINE__));
#endif

    //std::cout << "Start from " << script->GetParentObject()->GetName() << std::endl;

    Player = Core::Factory::CreateObject();
    Player->SetName("TestObject");

#if WINDOWS_MANAGER_INCLUDED
    const auto windowsBuffer = Core::World::GetSystemData("WindowsBuffer");
    if (windowsBuffer == nullptr) {
        Core::Logger::LogError("Failed to get windows buffer: " + __LOGERROR__);
        return;
    }
    const auto windows = reinterpret_cast<WindowsManager::WindowsBuffer*>(windowsBuffer);

    win1 = windows->CreateWindow(1280, 720, "Windows 1");
    win2 = windows->CreateWindow(400, 400, "Windows 2");
    win1->SetCursorVisible(false);
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

        auto showCursor = buffer->CreateKeyboardBind(
            { std::bind(&MyScript::ShowCursor, this) },
            { EnumKeyboardKeysStates::KeyPressed },
            { EnumKeyboardTable::LAlt },
            win1);

        auto hideCursor = buffer->CreateKeyboardBind(
            { std::bind(&MyScript::HideCursor, this) },
            { EnumKeyboardKeysStates::KeyReleased },
            { EnumKeyboardTable::LAlt },
            win1
        );

        auto leftMove = buffer->CreateKeyboardBind(
            { std::bind(&MyScript::LeftMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::A },
            win1
        );

        auto rightMove = buffer->CreateKeyboardBind(
            { std::bind(&MyScript::RightMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::D },
            win1
        );

        auto forwardMove = buffer->CreateKeyboardBind(
            { std::bind(&MyScript::ForwardMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::W },
            win1
        );

        auto backwardMove = buffer->CreateKeyboardBind(
            { std::bind(&MyScript::BackwardMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::S },
            win1
        );

        auto upMove = buffer->CreateKeyboardBind(
            { std::bind(&MyScript::UpMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::Q },
            win1
        );

        auto downMove = buffer->CreateKeyboardBind(
            { std::bind(&MyScript::DownMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::E },
            win1
        );


        auto rotateBind = buffer->CreateMouseSensorBind(
            { std::bind(&MyScript::CameraRotate, this) },
            { EnumMouseSensorStates::MouseKeepMoved, EnumMouseSensorStates::MouseStartMoved },
            win1
        );

        //bind->IsActive = false;
    }
#endif

#if ANOMALY_ENGINE_INCLUDED
    auto cam1 = camerasBuffer->CreateCamera();
    auto cam2 = camerasBuffer->CreateCamera();

    cam1->SetRenderWindow(win1->GetGLFWwindow());
    cam2->SetRenderWindow(win2->GetGLFWwindow());

    Player->AddComponent(cam1);

    auto obj3 = Core::Factory::CreateObject();
    obj3->AddComponent(cam2);

    auto obj2 = Core::Factory::CreateObject();
    obj2->SetName("Mesh");
    auto mesh = meshesBuffer->CreateMesh("/Engine_Assets/Models/Primitives/Cube.fbx");
    obj2->AddComponent(mesh);

    mesh->_material.InitShader<AnomalyEngine::CubeMapShader>();
    static_cast<AnomalyEngine::CubeMapShader*>(mesh->_material.Shader.get())->LoadTextures(
        R"(/Engine_Assets/Textures/CubeMap/Left_Tex.tga)",
        R"(/Engine_Assets/Textures/CubeMap/Right_Tex.tga)",
        R"(/Engine_Assets/Textures/CubeMap/Top_Tex.tga)",
        R"(/Engine_Assets/Textures/CubeMap/Bottom_Tex.tga)",
        R"(/Engine_Assets/Textures/CubeMap/Front_Tex.tga)",
        R"(/Engine_Assets/Textures/CubeMap/Back_Tex.tga)"
    );

    auto cube = Core::Factory::CreateObject();

    cube->transform.AddPosition(0, -5, -25);
    cube->transform.AddRotation(0, 0, 0);
    cube->transform.SetScale(50, 0.5, 50);

    cube->SetName("Cube");

    auto cubeMesh = meshesBuffer->CreateMesh("/Engine_Assets/Models/Primitives/Cube.fbx");
    cube->AddComponent(cubeMesh);

    cubeMesh->_material.InitShader<AnomalyEngine::OpaqueShader>();
    static_cast<AnomalyEngine::OpaqueShader*>(cubeMesh->_material.Shader.get())->LoadTextures(
        "/Engine_Assets/Textures/Planets/8k_earth_daymap.jpeg",
        "",
        "",
        "",
        "",
        "/Engine_Assets/Textures/Planets/8k_earth_nightmap.jpg");

    auto LightsSource = Core::Factory::CreateObject();
    LightsSource->transform.AddPosition(0,5,0);

    auto dirLight = directLightsBuffer->CreateDirectLight();
    dirLight->Intensity = 0.1;
    LightsSource->AddComponent(dirLight);

    auto pointLight = pointLightsBuffer->CreatePointLight();
    pointLight->Intensity = 100;
    LightsSource->AddComponent(pointLight);
#endif
}
//Call every frame
void MyScript::Update() {
    Core::Logger::LogInfo(Core::World::GetDeltaTime());
}
//Call before deleted
void MyScript::End() {

}