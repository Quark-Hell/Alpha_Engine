#include "Factory.h"

#include "EngineConfig.h"

#include "World.h"
#include "Object.h"
#include "Components/Component.h"

#include "Logger/Logger.h"

bool Core::Factory::RemoveObject(const Core::Object* object) {
  const auto list = World::GetObjects();
  auto it = std::begin(*list);

  for (size_t i = 0; i < World::GetObjects()->size(); ++i) {
    if (it->get() == &object[i]) {
      Core::Logger::LogInfo("Removing object");
      World::GetObjects()->erase(it);
      Core::Logger::LogInfo("Object removed");
      return true;
    }
    std::advance(it, 1);
  }

  Core::Logger::LogInfo("Object do not exist");
  return false;
}

Core::Object* Core::Factory::CreateObject() {
  World::GetObjects()->emplace_back(std::unique_ptr<Core::Object>(new Core::Object()));
  Core::Logger::LogInfo("Object created");
  return World::GetObjects()->back().get();
}

#if ANOMALY_ENGINE_INCLUDED
Render::WindowsManager::AnomalyEngine::Camera* Core::Factory::CreateCamera(const float fov, const float aspect, const float zNear, const float zFar) {
  const auto cameras = World::GetCameras();

  cameras->emplace_back(std::unique_ptr<Render::WindowsManager::AnomalyEngine::Camera>
    (new Render::WindowsManager::AnomalyEngine::Camera(fov, aspect, zNear, zFar)));

  Core::Logger::LogInfo("Camera created");
  return static_cast<Render::WindowsManager::AnomalyEngine::Camera*>(cameras->back().get());
}

bool Core::Factory::RemoveCamera(const Render::WindowsManager::AnomalyEngine::Camera* camera) {
  const auto list = World::GetCameras();
  auto it = std::begin(*list);

  for (size_t i = 0; i < World::GetCameras()->size(); ++i) {
    if (it->get() == &camera[i]) {
      Core::Logger::LogInfo("Removing camera");
      World::GetCameras()->erase(it);
      Core::Logger::LogInfo("Camera removed");
      return true;
    }
    std::advance(it, 1);
  }

  Core::Logger::LogError("Camera cannot be removed: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
  return false;
}

Render::WindowsManager::AnomalyEngine::Mesh* Core::Factory::CreateMesh() {
  const auto meshes = World::GetMeshes();

  meshes->emplace_back(std::unique_ptr<Render::WindowsManager::AnomalyEngine::Mesh>
    (new Render::WindowsManager::AnomalyEngine::Mesh()));

  Core::Logger::LogInfo("Mesh created");

  return static_cast<Render::WindowsManager::AnomalyEngine::Mesh*>(meshes->back().get());
}

Render::WindowsManager::AnomalyEngine::Mesh* Core::Factory::CreateMesh(const std::string& path) {
  const auto meshes = World::GetMeshes();

  meshes->emplace_back(std::unique_ptr<Render::WindowsManager::AnomalyEngine::Mesh>
    (new Render::WindowsManager::AnomalyEngine::Mesh()));

  static_cast<Render::WindowsManager::AnomalyEngine::Mesh*>(meshes->back().get())->Create(path);

  Core::Logger::LogInfo("Mesh created");

  return static_cast<Render::WindowsManager::AnomalyEngine::Mesh*>(meshes->back().get());
}

Render::WindowsManager::AnomalyEngine::DirectLight* Core::Factory::CreateDirectLight(const Core::Vector3& direction) {
  const auto lights = World::GetDirectLights();

  lights->emplace_back(std::unique_ptr<Render::WindowsManager::AnomalyEngine::DirectLight>
    (new Render::WindowsManager::AnomalyEngine::DirectLight(direction)));

  Core::Logger::LogInfo("Direct light created");

  return static_cast<Render::WindowsManager::AnomalyEngine::DirectLight*>(lights->back().get());
}

Render::WindowsManager::AnomalyEngine::PointLight* Core::Factory::CreatePointLight(const float radius, const float constant, const float linear, const float quadratic) {
  const auto lights = World::GetPointLights();

  lights->emplace_back(std::unique_ptr<Render::WindowsManager::AnomalyEngine::PointLight>
    (new Render::WindowsManager::AnomalyEngine::PointLight(radius, constant, linear, quadratic)));

  Core::Logger::LogInfo("Point light created");

  return static_cast<Render::WindowsManager::AnomalyEngine::PointLight*>(lights->back().get());
}
#endif



