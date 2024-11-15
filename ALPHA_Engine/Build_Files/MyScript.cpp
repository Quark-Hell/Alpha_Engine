#include "MyScript.h"
#include "Core/Object.h"
#include "Core/Factory.h"
#include "Core/Logger/Logger.h"

#include "Render/WinManager/AnomalyEngine/Components/Mesh.h"
#include "Render/WinManager/AnomalyEngine/Components/Camera.h"
#include "Render/WinManager/Window.h"

#include "Render/WinManager/AnomalyEngine/Shaders/CubeMapShader.h"
#include "Render/WinManager/AnomalyEngine/Shaders/OpaqueShader.h"

#include "Render/WinManager/BindsEngine/BindsEngineConfig.h"
#include "Render/WinManager/BindsEngine/InputSystem.h"

#include <iostream>

MyScript* script = new MyScript();

void MyScript::CameraRotate() {
    if (win1->GetCursorVisible() == true)
        return;

    float sensitive = 0.15;
    const auto bind = Render::WindowsManager::BindsEngine::InputSystem::GetInstance();
    std::cout << "X: " << bind->GetMouse()->GetMouseDelta().X << " Y: " << bind->GetMouse()->GetMouseDelta().Y << std::endl;

    if (bind->GetMouse()->IsMouseChangePosition()) {

        Core::Vector3 delta;
        delta.X = bind->GetMouse()->GetMouseDelta().X;
        delta.Y = bind->GetMouse()->GetMouseDelta().Y;

        if (delta.GetMagnitude() > 1) {

            auto newRot = static_cast<Core::Vector3>(Player->transform.GetRotation());

            newRot.X += delta.Y * sensitive;
            newRot.Y += delta.X * sensitive;

            Player->transform.SetRotation(newRot);
        }
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

    newPos += UpVector * moveSensitive;

    Player->transform.SetPosition(newPos);
}

void MyScript::RightMoveCamera() {
    Core::Vector3 newPos = Player->transform.GetPosition();

    Core::Vector3 UpVector;

    UpVector.X = sin((Player->transform.GetRotation().Y + 90) * 3.14159 / 180);
    UpVector.Y = 0;
    UpVector.Z = sin((Player->transform.GetRotation().Y) * 3.14159 / 180);

    newPos += UpVector * (-moveSensitive);

    Player->transform.SetPosition(newPos);
}
void MyScript::ForwardMoveCamera() {
    Core::Vector3 newPos = Player->transform.GetPosition();

    Core::Vector3 ForwardVector{ 0,0,0 };

    ForwardVector.X = sin((Player->transform.GetRotation().Y + 180) * 3.14159 / 180); // RIGHT
    ForwardVector.Y = cos((Player->transform.GetRotation().X + 270) * 3.14159 / 180); // RIGHT
    ForwardVector.Z = sin((Player->transform.GetRotation().Y + 90) * 3.14159 / 180); // RIGHT

    newPos += ForwardVector * moveSensitive;

    Player->transform.SetPosition(newPos);
}
void MyScript::BackwardMoveCamera() {
    Core::Vector3 newPos = Player->transform.GetPosition();

    Core::Vector3 BackwardVector{ 0,0,0 };

    BackwardVector.X = sin((Player->transform.GetRotation().Y + 180) * 3.14159 / 180); // RIGHT
    BackwardVector.Y = cos((Player->transform.GetRotation().X + 270) * 3.14159 / 180); // RIGHT
    BackwardVector.Z = sin((Player->transform.GetRotation().Y + 90) * 3.14159 / 180); // RIGHT

    newPos += BackwardVector * (-moveSensitive);

    Player->transform.SetPosition(newPos);
}

void MyScript::UpMoveCamera() {
    Core::Vector3 newPos = Player->transform.GetPosition();

    newPos.Y += moveSensitive;

    Player->transform.SetPosition(newPos);
}
void MyScript::DownMoveCamera() {
    Core::Vector3 newPos = Player->transform.GetPosition();

    newPos.Y -= moveSensitive;

    Player->transform.SetPosition(newPos);
}

//Call after created
void MyScript::Start() {
    auto logger = Core::Logger::Logger::GetInstance();
    logger->LoggerError("NIGGER ALARM");


    std::cout << "Start from " << script->GetParentObject()->GetName() << std::endl;

    Player = Core::Factory::CreateObject();
    Player->SetName("TestObject");

#if RENDER_INCLUDED
    win1 = Core::Factory::CreateWindow(1280, 720, "Windows 1");
    win2 = Core::Factory::CreateWindow(400, 400, "Windows 2");
    win1->SetCursorVisible(false);
#endif

#if BINDS_ENGINE_INCLUDED
    {
        using namespace Render::WindowsManager::BindsEngine;

        auto showCursor = Core::Factory::CreateKeyboardBind(
            { std::bind(&MyScript::ShowCursor, this) },
            { EnumKeyboardKeysStates::KeyPressed },
            { EnumKeyboardTable::LAlt },
            win1
        );

        auto hideCursor = Core::Factory::CreateKeyboardBind(
            { std::bind(&MyScript::HideCursor, this) },
            { EnumKeyboardKeysStates::KeyReleased },
            { EnumKeyboardTable::LAlt },
            win1
        );

        auto leftMove = Core::Factory::CreateKeyboardBind(
            { std::bind(&MyScript::LeftMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::A },
            win1
        );

        auto rightMove = Core::Factory::CreateKeyboardBind(
            { std::bind(&MyScript::RightMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::D },
            win1
        );

        auto forwardMove = Core::Factory::CreateKeyboardBind(
            { std::bind(&MyScript::ForwardMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::W },
            win1
        );

        auto backwardMove = Core::Factory::CreateKeyboardBind(
            { std::bind(&MyScript::BackwardMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::S },
            win1
        );

        auto upMove = Core::Factory::CreateKeyboardBind(
            { std::bind(&MyScript::UpMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::Q },
            win1
        );

        auto downMove = Core::Factory::CreateKeyboardBind(
            { std::bind(&MyScript::DownMoveCamera, this) },
            { EnumKeyboardKeysStates::KeyHold },
            { EnumKeyboardTable::E },
            win1
        );


        auto rotateBind = Core::Factory::CreateMouseSensorBind(
            { std::bind(&MyScript::CameraRotate, this) },
            static_cast<Render::WindowsManager::BindsEngine::EnumMouseSensorStates>
            (EnumMouseSensorStates::MouseKeepMoved),
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

    mesh->_material.InitShader<Render::AnomalyEngine::Shaders::CubeMapShader>();
    static_cast<Render::AnomalyEngine::Shaders::CubeMapShader*>(mesh->_material.Shader.get())->LoadTextures(
        R"(/ALPHA_Engine/Engine_Assets/Textures/CubeMap/Left_Tex.tga)",
        R"(/ALPHA_Engine/Engine_Assets/Textures/CubeMap/Right_Tex.tga)",
        R"(/ALPHA_Engine/Engine_Assets/Textures/CubeMap/Top_Tex.tga)",
        R"(/ALPHA_Engine/Engine_Assets/Textures/CubeMap/Bottom_Tex.tga)",
        R"(/ALPHA_Engine/Engine_Assets/Textures/CubeMap/Front_Tex.tga)",
        R"(/ALPHA_Engine/Engine_Assets/Textures/CubeMap/Back_Tex.tga)"
    );

    auto cube = Core::Factory::CreateObject();
    cube->transform.AddPosition(0, 0, -5);
    cube->SetName("Cube");
    auto cubeMesh = Core::Factory::CreateMesh("/ALPHA_Engine/Engine_Assets/Models/Primitives/Sphere.fbx");
    cube->AddComponent(cubeMesh);
    cubeMesh->_material.InitShader<Render::AnomalyEngine::Shaders::OpaqueShader>();
    static_cast<Render::AnomalyEngine::Shaders::OpaqueShader*>(cubeMesh->_material.Shader.get())->LoadTextures(
        "/ALPHA_Engine/Engine_Assets/Textures/Planets/planet_continental_Base_Color.tga");
#endif
}
//Call every frame
void MyScript::Update() {
    //std::cout << "Test" <<std::endl;
}
//Call before deleted
void MyScript::End() {

}