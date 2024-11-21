#include "MyScript.h"
#include "Core/Object.h"
#include "Core/Factory.h"

#include "Logger/Logger.h"

#include "Render/WinManager/AnomalyEngine/Components/DirectLight.h"
#include "Render/WinManager/AnomalyEngine/Components/PointLight.h"

#include "Render/WinManager/AnomalyEngine/Components/Mesh.h"
#include "Render/WinManager/AnomalyEngine/Components/Camera.h"

#include "Render/WinManager/Window.h"
#include "Render/WinManager/WindowsBuffer.h"

#include "Render/WinManager/BindsEngine/BindsBuffer.h"

#include "Render/WinManager/AnomalyEngine/Shaders/CubeMapShader.h"
#include "Render/WinManager/AnomalyEngine/Shaders/OpaqueShader.h"

#include "Render/WinManager/BindsEngine/BindsEngineConfig.h"
#include "Render/WinManager/BindsEngine/InputSystem.h"

#include "Core/World.h"

MyScript* script = new MyScript();

void MyScript::CameraRotate() {
    if (win1->GetCursorVisible() == true)
        return;

    double sensitive = 7;
    sensitive *= Core::World::GetDeltaTime();
    const auto bind = Render::WindowsManager::BindsEngine::InputSystem::GetInstance();

    if (bind->GetMouse()->IsMouseChangePosition()) {

        Core::Vector3 delta;
        delta.X = bind->GetMouse()->GetMouseDelta().X;
        delta.Y = bind->GetMouse()->GetMouseDelta().Y;

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
    Logger::Logger::LogInfo("TestLoggerEvent");
    Logger::Logger::LogWarning("TestLoggerWarning");
    Logger::Logger::LogError("TestLoggerError: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
    //Logger::Logger::LogCritical("TestLoggerCritical: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
#endif

    std::cout << "Start from " << script->GetParentObject()->GetName() << std::endl;

    Player = Core::Factory::CreateObject();
    Player->SetName("TestObject");

#if RENDER_INCLUDED
    win1 = Render::WindowsManager::WindowsBuffer::CreateWindow(1280, 720, "Windows 1");
    win2 = Render::WindowsManager::WindowsBuffer::CreateWindow(400, 400, "Windows 2");
    win1->SetCursorVisible(false);
#endif

#if BINDS_ENGINE_INCLUDED
    {
        using namespace Render::WindowsManager::BindsEngine;

        auto showCursor = BindsBuffer::CreateKeyboardBind(
            { std::bind(&MyScript::ShowCursor, this) },
            { EnumKeyboardKeysStates::KeyPressed },
            { EnumKeyboardTable::LAlt },
            win1);

        auto hideCursor = BindsBuffer::CreateKeyboardBind(
            { std::bind(&MyScript::HideCursor, this) },
            { EnumKeyboardKeysStates::KeyReleased },
            { EnumKeyboardTable::LAlt },
            win1
        );

        auto leftMove = BindsBuffer::CreateKeyboardBind(
            { std::bind(&MyScript::LeftMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::A },
            win1
        );

        auto rightMove = BindsBuffer::CreateKeyboardBind(
            { std::bind(&MyScript::RightMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::D },
            win1
        );

        auto forwardMove = BindsBuffer::CreateKeyboardBind(
            { std::bind(&MyScript::ForwardMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::W },
            win1
        );

        auto backwardMove = BindsBuffer::CreateKeyboardBind(
            { std::bind(&MyScript::BackwardMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::S },
            win1
        );

        auto upMove = BindsBuffer::CreateKeyboardBind(
            { std::bind(&MyScript::UpMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::Q },
            win1
        );

        auto downMove = BindsBuffer::CreateKeyboardBind(
            { std::bind(&MyScript::DownMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::E },
            win1
        );


        auto rotateBind = BindsBuffer::CreateMouseSensorBind(
            { std::bind(&MyScript::CameraRotate, this) },
            { EnumMouseSensorStates::MouseKeepMoved, EnumMouseSensorStates::MouseStartMoved },
            win1
        );

        //bind->IsActive = false;
    }
#endif

#if ANOMALY_ENGINE_INCLUDED
    auto cam1 = Core::Factory::CreateCamera();
    auto cam2 = Core::Factory::CreateCamera();

    win1->SetCamera(cam1);
    win2->SetCamera(cam2);

    Player->AddComponent(cam1);

    auto obj3 = Core::Factory::CreateObject();
    obj3->AddComponent(cam2);

    auto obj2 = Core::Factory::CreateObject();
    obj2->SetName("Mesh");
    auto mesh = Core::Factory::CreateMesh("/ALPHA_Engine/Engine_Assets/Models/Primitives/Cube.fbx");
    obj2->AddComponent(mesh);

    mesh->_material.InitShader<Render::WindowsManager::AnomalyEngine::CubeMapShader>();
    static_cast<Render::WindowsManager::AnomalyEngine::CubeMapShader*>(mesh->_material.Shader.get())->LoadTextures(
        R"(/ALPHA_Engine/Engine_Assets/Textures/CubeMap/Left_Tex.tga)",
        R"(/ALPHA_Engine/Engine_Assets/Textures/CubeMap/Right_Tex.tga)",
        R"(/ALPHA_Engine/Engine_Assets/Textures/CubeMap/Top_Tex.tga)",
        R"(/ALPHA_Engine/Engine_Assets/Textures/CubeMap/Bottom_Tex.tga)",
        R"(/ALPHA_Engine/Engine_Assets/Textures/CubeMap/Front_Tex.tga)",
        R"(/ALPHA_Engine/Engine_Assets/Textures/CubeMap/Back_Tex.tga)"
    );

    auto cube = Core::Factory::CreateObject();

    cube->transform.AddPosition(0, -5, -25);
    cube->transform.AddRotation(0, 0, 0);
    cube->transform.SetScale(50, 0.5, 50);

    cube->SetName("Cube");

    auto cubeMesh = Core::Factory::CreateMesh("/ALPHA_Engine/Engine_Assets/Models/Primitives/Cube.fbx");
    cube->AddComponent(cubeMesh);

    cubeMesh->_material.InitShader<Render::WindowsManager::AnomalyEngine::OpaqueShader>();
    static_cast<Render::WindowsManager::AnomalyEngine::OpaqueShader*>(cubeMesh->_material.Shader.get())->LoadTextures(
        "/ALPHA_Engine/Engine_Assets/Textures/Planets/8k_earth_daymap.jpeg",
        "",
        "",
        "",
        "",
        "/ALPHA_Engine/Engine_Assets/Textures/Planets/8k_earth_nightmap.jpg");

    auto LightsSource = Core::Factory::CreateObject();
    LightsSource->transform.AddPosition(0,5,0);

    auto dirLight = Core::Factory::CreateDirectLight();
    dirLight->Intensity = 0.1;
    LightsSource->AddComponent(dirLight);

    auto pointLight = Core::Factory::CreatePointLight();
    pointLight->Intensity = 100;
    LightsSource->AddComponent(pointLight);

#endif
}
//Call every frame
void MyScript::Update() {
    Logger::Logger::LogInfo(Core::World::GetDeltaTime());
}
//Call before deleted
void MyScript::End() {

}