#include "Modules.h"

#include "MyScript.h"

namespace Core {
    void InstanceModule() {
        userScriptsBuffer = new Register::UserScriptsBuffer(2);

        keyboardBuffer = new BindsEngine::KeyboardSensors();
        mouseBuffer = new BindsEngine::MouseSensors(8);

        inputSystem = new BindsEngine::InputSystem();
        bindsBuffer = new BindsEngine::BindsBuffer(16);

        windowsBuffer = new WindowsManager::WindowsBuffer(4);

        rigidBodiesBuffer = new AxisEngine::RigidBodiesBuffer(8);
        collidersBuffer = new AxisEngine::CollidersBuffer(8);

        meshesBuffer = new AnomalyEngine::MeshesBuffer(16);
        camerasBuffer = new AnomalyEngine::CamerasBuffer(16);
        directLightsBuffer = new AnomalyEngine::DirectLightsBuffer(4);
        pointLightsBuffer = new AnomalyEngine::PointLightsBuffer(4);

        userScriptSystem = new Register::Registry(100);
        mouseSystem = new BindsEngine::MouseSystem(200);
        keyboardSystem = new BindsEngine::KeyboardSystem(210);
        physicsSystem = new AxisEngine::PhysicsEngine(1000);
        collisionSystem = new AxisEngine::CollisionEngine(2000);
        windowsSystem = new WindowsManager::WindowsManager(3000);
        anomalySystem = new AnomalyEngine::RenderEngine(4000);


        IncludeScripts();
    }
}

void IncludeScripts() {
    /*auto* script =*/ userScriptsBuffer->CreateActor<MyScript>();
}