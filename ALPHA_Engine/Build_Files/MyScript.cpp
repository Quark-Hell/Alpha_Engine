#include "MyScript.h"
#include "Core/Object.h"
#include "Core/Factory.h"

#include "Render/WinManager/AnomalyEngine/Components/Mesh.h"
#include "Render/WinManager/AnomalyEngine/Components/Camera.h"
#include "Render/WinManager/Window.h"

#include "Render/WinManager/AnomalyEngine/Shaders/CubeMapShader.h"

#include "Render/WinManager/BindsEngine/Binds.h"
#include "Render/WinManager/BindsEngine/Keyboard/KeyboardSensors.h"

#include <iostream>

MyScript* script = new MyScript();

void MyScript::Print() {
    std::cout << "Hello Bind!" << std::endl;
}

//Call after created
void MyScript::Start() {
    std::cout << "Start from " << script->GetParentObject()->GetName() << std::endl;

#if RENDER_INCLUDED
    auto win1 = Core::Factory::CreateWindow(800, 600, "Windows 1");
    auto win2 = Core::Factory::CreateWindow(800, 600, "Windows 2");
#endif

#if BINDS_ENGINE_INCLUDED
    {
        using namespace Render::WindowsManager::BindsEngine;

        auto bind = Core::Factory::CreateKeyboardBind(
        {std::bind(&MyScript::Print, this),},
        {EnumKeyStates::KeyHold},
        {EnumKeyboardTable::A},
        win1);
    }
#endif

#if ANOMALY_ENGINE_INCLUDED
    auto cam1 = Core::Factory::CreateCamera();
    auto cam2 = Core::Factory::CreateCamera();

    win1->SetCamera(cam1);
    win2->SetCamera(cam2);

    auto obj1 = Core::Factory::CreateObject();
    obj1->SetName("TestObject");
    obj1->AddComponent(cam1);
    obj1->AddComponent(cam2);

    obj1->transform.AddPosition(0,0,-2);

    auto obj2 = Core::Factory::CreateObject();
    obj2->SetName("Mesh");
    auto mesh = Core::Factory::CreateMesh("/ALPHA_Engine/Engine_Assets/Models/Primitives/Cube.fbx");
    obj2->AddComponent(mesh);
    mesh->_material.InitShader<Render::AnomalyEngine::Shaders::CubeMapShader>();
#endif

#if RENDER_INCLUDED
    auto win3 = Core::Factory::CreateWindow(800, 600, "Windows 3");
    auto win4 = Core::Factory::CreateWindow(800, 600, "Windows 4");
#endif

#if ANOMALY_ENGINE_INCLUDED
    win3->SetCamera(cam1);
    win4->SetCamera(cam1);
#endif
}
//Call every frame
void MyScript::Update() {
    //std::cout << "Test" <<std::endl;
}
//Call before deleted
void MyScript::End() {

}