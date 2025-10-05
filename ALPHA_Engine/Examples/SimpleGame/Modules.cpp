#include "Modules.h"

#include "MyScript.h"

namespace Core {
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

        axisSystem = new AxisEngine::PhysicsEngine();
        rigidBodiesBuffer = new AxisEngine::RigidBodiesBuffer();

        IncludeScripts();
    }
}

void IncludeScripts() {
    /*auto* script =*/ userScriptsBuffer->CreateActor<MyScript>();
}