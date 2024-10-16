#include "MyScript.h"
#include "Core/Object.h"
#include "Core/Factory.h"

#include "Anomaly/WinManager/AnomalyEngine/Components/Camera.h"
#include "Anomaly/WinManager/Window.h"

#include <iostream>

MyScript* script = new MyScript();

//Call after created
void MyScript::Start() {
    std::cout << "Start from " << script->GetParentObject().GetName() << std::endl;
#if ANOMALY_ENGINE_INCLUDED
    auto win1 = Core::Factory::CreateWindow(400, 600, "Windows 1");
    auto win2 = Core::Factory::CreateWindow(800, 600, "Windows 2");

    auto cam1 = Core::Factory::CreateCamera();
    auto cam2 = Core::Factory::CreateCamera();

    win1->SetCamera(cam1);
    win2->SetCamera(cam2);

#endif
}
//Call every frame
void MyScript::Update() {
    //std::cout << "Test" <<std::endl;
}
//Call before deleted
void MyScript::End() {

}