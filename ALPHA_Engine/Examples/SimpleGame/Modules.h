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
#include "AnomalyEngine/Shaders/SimplexFractalShader.h"
//===================Anomaly Engine===================//

//===================Axis Engine======================//
#include "AxisEngine/Systems/CollisionEngine.h"
#include "AxisEngine/Systems/PhysicsEngine.h"

#include "AxisEngine/Buffers/CollidersBuffer.h"
#include "AxisEngine/Buffers/RigidBodiesBuffer.h"

#include "AxisEngine/Components/AABB.h"
#include "AxisEngine/Components/Collider.h"
#include "AxisEngine/Components/CubeCollider.h"
#include "AxisEngine/Components/MeshCollider.h"
#include "AxisEngine/Components/SphereCollider.h"
#include "AxisEngine/Components/Rigidbody.h"
//===================Axis Engine======================//

//===================User Scripts Register===================//
inline Register::Registry* userScriptSystem = nullptr;
inline Register::UserScriptsBuffer* userScriptsBuffer  = nullptr;
//===================User Scripts Register===================//

//===================Binds Engine===================//
inline BindsEngine::KeyboardSystem* keyboardSystem = nullptr;
inline BindsEngine::KeyboardSensors* keyboardBuffer  = nullptr;

inline BindsEngine::MouseSystem* mouseSystem = nullptr;
inline BindsEngine::MouseSensors* mouseBuffer = nullptr;

inline BindsEngine::InputSystem* inputSystem = nullptr;
inline BindsEngine::BindsBuffer* bindsBuffer = nullptr;
//===================Binds Engine===================//

//===================Windows Manager===================//
inline WindowsManager::WindowsManager* windowsSystem = nullptr;
inline WindowsManager::WindowsBuffer* windowsBuffer = nullptr;
//===================Windows Manager===================//

//===================Anomaly Engine===================//
inline AnomalyEngine::RenderEngine* anomalySystem = nullptr;
inline AnomalyEngine::MeshesBuffer* meshesBuffer = nullptr;
inline AnomalyEngine::CamerasBuffer* camerasBuffer = nullptr;
inline AnomalyEngine::DirectLightsBuffer* directLightsBuffer = nullptr;
inline AnomalyEngine::PointLightsBuffer* pointLightsBuffer = nullptr;
//===================Anomaly Engine===================//

//===================Axis Engine======================//
inline AxisEngine::PhysicsEngine* physicsSystem = nullptr;
inline AxisEngine::CollisionEngine* collisionSystem = nullptr;
inline AxisEngine::RigidBodiesBuffer* rigidBodiesBuffer = nullptr;
inline AxisEngine::CollidersBuffer* collidersBuffer = nullptr;
//===================Axis Engine======================//

void IncludeScripts();