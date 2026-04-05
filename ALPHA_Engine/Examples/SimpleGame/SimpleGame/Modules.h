#pragma once

//===================Core===================//
#include "Core/World.h"
#include "Core/Objects/Object.h"
#include "Core/Objects/GameObject.h"
#include "Core/Objects/FakeObject.h"
#include "Core/Factory.h"

#include "Core/Timer.h"

#include "Core/Logger/Logger.h"
//===================Core===================//

#include "UserScriptsRegister/UserScriptConfig.h"
#ifdef WINDOWS_MANAGER_INCLUDED
	#include "WindowsManager/WindowsManagerConfig.h"
#endif

//===================Binds Engine===================//
#if BINDS_ENGINE_INCLUDED
#include "BindsEngine/InputSystem.h"

#include "BindsEngine/Binds.h"
#include "BindsEngine/BindsBuffer.h"

#include "BindsEngine/Keyboard/Keyboard.h"
#include "BindsEngine/Keyboard/KeyboardSensors.h"

#include "BindsEngine/Mouse/Mouse.h"
#include "BindsEngine/Mouse/MouseSensors.h"
#endif
//===================Binds Engine===================//

//===================Anomaly Engine===================//
#if ANOMALY_ENGINE_INCLUDED
#include "AnomalyEngine/RenderEngine.h"

#include "AnomalyEngine/Buffers/CamerasBuffer.h"
#include "AnomalyEngine/Buffers/MeshesBuffer.h"
#include "AnomalyEngine/Buffers/TempMeshesBuffer.h"
#include "AnomalyEngine/Buffers/DirectLightsBuffer.h"
#include "AnomalyEngine/Buffers/PointLightsBuffer.h"

#include "AnomalyEngine/Components/Mesh.h"
#include "AnomalyEngine/Components/Camera.h"
#include "AnomalyEngine/Components/DirectLight.h"
#include "AnomalyEngine/Components/PointLight.h"

#include "AnomalyEngine/Shaders/CubeMapShader.h"
#include "AnomalyEngine/Shaders/OpaqueShader.h"
#include "AnomalyEngine/Shaders/SimplexFractalShader.h"
#endif
//===================Anomaly Engine===================//

//===================Axis Engine======================//
#if AXIS_ENGINE_INCLUDED
#include "AxisEngine/Systems/PhysicsEngine.h"

#include "AxisEngine/Buffers/CollidersBuffer.h"
#include "AxisEngine/Buffers/RigidBodiesBuffer.h"

#include "AxisEngine/Components/AABB.h"
#include "AxisEngine/Components/Collider.h"
#include "AxisEngine/Components/CubeCollider.h"
#include "AxisEngine/Components/ConvexMeshCollider.h"
#include "AxisEngine/Components/SphereCollider.h"
#include "AxisEngine/Components/Rigidbody.h"
#endif
//===================Axis Engine======================//


//===================Sonar Engine======================//
#if SONAR_ENGINE_INCLUDED
#include "SonarEngine/Buffers/AudioSourcesBuffer.h"
#include "SonarEngine/Buffers/AudioListenersBuffer.h"
#include "SonarEngine/Systems/SonarEngine.h"
#endif
//===================Sonar Engine======================//











//===================User Scripts Register===================//
inline Register::Registry* userScriptSystem = nullptr;
inline Register::UserScriptsBuffer* userScriptsBuffer  = nullptr;
//===================User Scripts Register===================//

//===================Binds Engine===================//
#if BINDS_ENGINE_INCLUDED
inline BindsEngine::KeyboardSystem* keyboardSystem = nullptr;
inline BindsEngine::KeyboardSensors* keyboardBuffer  = nullptr;

inline BindsEngine::MouseSystem* mouseSystem = nullptr;
inline BindsEngine::MouseSensors* mouseBuffer = nullptr;

inline BindsEngine::InputSystem* inputSystem = nullptr;
inline BindsEngine::BindsBuffer* bindsBuffer = nullptr;
#endif
//===================Binds Engine===================//

//===================Windows Manager===================//
#if WINDOWS_MANAGER_INCLUDED
inline WindowsManager::WindowsManager* windowsSystem = nullptr;
inline WindowsManager::WindowsBuffer* windowsBuffer = nullptr;
#endif
//===================Windows Manager===================//

//===================Anomaly Engine===================//
#if ANOMALY_ENGINE_INCLUDED
inline AnomalyEngine::RenderEngine* anomalySystem = nullptr;
inline AnomalyEngine::MeshesBuffer* meshesBuffer = nullptr;
inline AnomalyEngine::TempMeshesBuffer* tempMeshesBuffer = nullptr;
inline AnomalyEngine::CamerasBuffer* camerasBuffer = nullptr;
inline AnomalyEngine::DirectLightsBuffer* directLightsBuffer = nullptr;
inline AnomalyEngine::PointLightsBuffer* pointLightsBuffer = nullptr;
#endif
//===================Anomaly Engine===================//

//===================Axis Engine======================//
#if AXIS_ENGINE_INCLUDED
inline AxisEngine::PhysicsEngine* physicsSystem = nullptr;
inline AxisEngine::RigidBodiesBuffer* rigidBodiesBuffer = nullptr;
inline AxisEngine::CollidersBuffer* collidersBuffer = nullptr;
#endif
//===================Axis Engine======================//

//===================Sonar Engine======================//
#if SONAR_ENGINE_INCLUDED
inline SonarEngine::SonarEngine* audioSystem = nullptr;
inline SonarEngine::AudioSourcesBuffer* audioSourcesBuffer = nullptr;
inline SonarEngine::AudioListenersBuffer* audioListenersBuffer = nullptr;
#endif
//===================Sonar Engine======================//

void IncludeScripts();