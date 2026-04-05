#include "Modules.h"

#include "EngineScripts/MyScript.h"
#include "EngineScripts/Player.h"
#include "EngineScripts/WorldBuilder.h"

#include "Windows/WindowsSettings.h"

namespace Core {
    void InstanceModule() {
        userScriptsBuffer = new Register::UserScriptsBuffer(2);

#if BINDS_ENGINE_INCLUDED
        keyboardBuffer = new BindsEngine::KeyboardSensors();
        mouseBuffer = new BindsEngine::MouseSensors(8);

        inputSystem = new BindsEngine::InputSystem();
        bindsBuffer = new BindsEngine::BindsBuffer(16);
#endif

#if WINDOWS_MANAGER_INCLUDED
        windowsBuffer = new WindowsManager::WindowsBuffer(4);
#endif

#if AXIS_ENGINE_INCLUDED
        rigidBodiesBuffer = new AxisEngine::RigidBodiesBuffer(8);
        collidersBuffer = new AxisEngine::CollidersBuffer(8);
#endif

#if ANOMALY_ENGINE_INCLUDED
        meshesBuffer = new AnomalyEngine::MeshesBuffer(16);
        tempMeshesBuffer = new AnomalyEngine::TempMeshesBuffer(16);
        camerasBuffer = new AnomalyEngine::CamerasBuffer(16);
        directLightsBuffer = new AnomalyEngine::DirectLightsBuffer(4);
        pointLightsBuffer = new AnomalyEngine::PointLightsBuffer(4);
#endif

#if SONAR_ENGINE_INCLUDED
        audioSourcesBuffer = new SonarEngine::AudioSourcesBuffer(8);
        audioListenersBuffer = new SonarEngine::AudioListenersBuffer(1);
#endif








        userScriptSystem = new Register::Registry(1000);
#if BINDS_ENGINE_INCLUDED
        mouseSystem = new BindsEngine::MouseSystem(2000);
        keyboardSystem = new BindsEngine::KeyboardSystem(2500);
#endif

#if AXIS_ENGINE_INCLUDED
        physicsSystem = new AxisEngine::PhysicsEngine(3000);
#endif

#if SONAR_ENGINE_INCLUDED
        audioSystem = new SonarEngine::SonarEngine(4000);
#endif

#if WINDOWS_MANAGER_INCLUDED
        windowsSystem = new WindowsManager::WindowsManager(5000);
#endif

#if ANOMALY_ENGINE_INCLUDED
        anomalySystem = new AnomalyEngine::RenderEngine(6000);
#endif


        IncludeScripts();
    }
}

void IncludeScripts() {
    auto* script = userScriptsBuffer->CreateActor<MyScript>("MyScript");
    auto* playerScript = userScriptsBuffer->CreateActor<Player>("Player");
    auto* worldBuilder = userScriptsBuffer->CreateActor<WorldBuilder>("WorldBuilder");
    auto* windowsSettings = userScriptsBuffer->CreateActor<WindowsSettings>("WindowsSettings");
}