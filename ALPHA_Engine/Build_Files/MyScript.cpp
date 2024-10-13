#include "MyScript.h"
#include "Core/Object.h"
#include "Core/Factory.h"
#include <iostream>

MyScript* script = new MyScript();

//Call after created
void MyScript::Start() {
    std::cout << "Start from " << script->GetParentObject().GetName() << std::endl;
#if ANOMALY_ENGINE_INCLUDED
    Core::Factory::CreateWindow(800, 600, "Windows1");
    Core::Factory::CreateWindow(800, 600, "Windows2");
#endif
}
//Call every frame
void MyScript::Update() {

}
//Call before deleted
void MyScript::End() {

}