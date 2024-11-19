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
      Logger::Logger::LogInfo("Removing object");
      World::GetObjects()->erase(it);
      Logger::Logger::LogInfo("Object removed");
      return true;
    }
    std::advance(it, 1);
  }

  Logger::Logger::LogInfo("Object do not exist");
  return false;
}

Core::Object* Core::Factory::CreateObject() {
  World::GetObjects()->emplace_back(std::unique_ptr<Core::Object>(new Core::Object()));
  Logger::Logger::LogInfo("Object created");
  return World::GetObjects()->back().get();
}

#if USER_SCRIPTS_REGISTER_INCLUDED
Register::UserScript* Core::Factory::CreateUserScript() {
  World::GetUserScripts()->emplace_back(std::unique_ptr<Register::UserScript>(new Register::UserScript()));
  return static_cast<Register::UserScript*>(World::GetUserScripts()->back().get());
}

bool Core::Factory::RemoveUserScript(const Core::Component* script) {
  const auto list = World::GetUserScripts();
  auto it = std::begin(*list);
  for (size_t i = 0; i < World::GetObjects()->size(); ++i) {
    if (it->get() == &script[i]) {
      Logger::Logger::LogInfo("Removing user script");
      World::GetUserScripts()->erase(it);
      Logger::Logger::LogInfo("User script removed");
      return true;
    }
    std::advance(it, 1);
  }

  Logger::Logger::LogError("User script do not exist: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
  return false;
}

Register::UserScript* Core::Factory::CreateUserScript(Core::Component* script) {
  const auto src = dynamic_cast<Register::UserScript*>(script);
  if (src == nullptr) {
    Logger::Logger::LogError("Argument is not a User Script type: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
    return nullptr;
  }

  const auto userScripts = World::GetUserScripts();
  for (auto& it : *userScripts) {
    if (src == it.get()) {
      Logger::Logger::LogError("User script already exist: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
      return nullptr;
    }
  }

  userScripts->emplace_back(std::unique_ptr<Register::UserScript>(src));
  return static_cast<Register::UserScript*>(World::GetUserScripts()->back().get());
}
#endif


#if RENDER_INCLUDED
Render::WindowsManager::Window* Core::Factory::CreateWindow(const int width, const int height, const char* title) {
  using namespace Render::WindowsManager;

  const auto windows = Core::World::GetWindows();

  if (windows->size() >= 1) {
    windows->emplace_back(std::unique_ptr<Window>
(new Window(width,height, title,nullptr,windows->at(0)->_window)));

    Logger::Logger::LogInfo("Created shared window");
  }
  else {
    windows->emplace_back(std::unique_ptr<Window>
(new Window(width,height, title,nullptr,nullptr)));

    Logger::Logger::LogInfo("Window created");
  }

  return windows->back().get();
}
#endif

#if ANOMALY_ENGINE_INCLUDED
Render::WindowsManager::AnomalyEngine::Camera* Core::Factory::CreateCamera(const float fov, const float aspect, const float zNear, const float zFar) {
  const auto cameras = World::GetCameras();

  cameras->emplace_back(std::unique_ptr<Render::WindowsManager::AnomalyEngine::Camera>
    (new Render::WindowsManager::AnomalyEngine::Camera(fov, aspect, zNear, zFar)));

  Logger::Logger::LogInfo("Camera created");
  return static_cast<Render::WindowsManager::AnomalyEngine::Camera*>(cameras->back().get());
}

bool Core::Factory::RemoveCamera(const Render::WindowsManager::AnomalyEngine::Camera* camera) {
  const auto list = World::GetCameras();
  auto it = std::begin(*list);

  for (size_t i = 0; i < World::GetCameras()->size(); ++i) {
    if (it->get() == &camera[i]) {
      Logger::Logger::LogInfo("Removing camera");
      World::GetCameras()->erase(it);
      Logger::Logger::LogInfo("Camera removed");
      return true;
    }
    std::advance(it, 1);
  }

  Logger::Logger::LogError("Camera cannot be removed: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
  return false;
}

Render::WindowsManager::AnomalyEngine::Mesh* Core::Factory::CreateMesh() {
  const auto meshes = World::GetMeshes();

  meshes->emplace_back(std::unique_ptr<Render::WindowsManager::AnomalyEngine::Mesh>
    (new Render::WindowsManager::AnomalyEngine::Mesh()));

  Logger::Logger::LogInfo("Mesh created");

  return static_cast<Render::WindowsManager::AnomalyEngine::Mesh*>(meshes->back().get());
}

Render::WindowsManager::AnomalyEngine::Mesh* Core::Factory::CreateMesh(const std::string& path) {
  const auto meshes = World::GetMeshes();

  meshes->emplace_back(std::unique_ptr<Render::WindowsManager::AnomalyEngine::Mesh>
    (new Render::WindowsManager::AnomalyEngine::Mesh()));

  static_cast<Render::WindowsManager::AnomalyEngine::Mesh*>(meshes->back().get())->Create(path);

  Logger::Logger::LogInfo("Mesh created");

  return static_cast<Render::WindowsManager::AnomalyEngine::Mesh*>(meshes->back().get());
}

Render::WindowsManager::AnomalyEngine::DirectLight* Core::Factory::CreateDirectLight(const Core::Vector3& direction) {
  const auto lights = World::GetDirectLights();

  lights->emplace_back(std::unique_ptr<Render::WindowsManager::AnomalyEngine::DirectLight>
    (new Render::WindowsManager::AnomalyEngine::DirectLight(direction)));

  Logger::Logger::LogInfo("Direct light created");

  return static_cast<Render::WindowsManager::AnomalyEngine::DirectLight*>(lights->back().get());
}

Render::WindowsManager::AnomalyEngine::PointLight* Core::Factory::CreatePointLight(const float radius, const float constant, const float linear, const float quadratic) {
  const auto lights = World::GetPointLights();

  lights->emplace_back(std::unique_ptr<Render::WindowsManager::AnomalyEngine::PointLight>
    (new Render::WindowsManager::AnomalyEngine::PointLight(radius, constant, linear, quadratic)));

  Logger::Logger::LogInfo("Point light created");

  return static_cast<Render::WindowsManager::AnomalyEngine::PointLight*>(lights->back().get());
}
#endif

#if BINDS_ENGINE_INCLUDED

Render::WindowsManager::BindsEngine::Bind* Core::Factory::CreateMouseButtonsBind(
  const std::vector<std::function<void(void)>>& Operations,
  const std::vector<Render::WindowsManager::BindsEngine::EnumMouseKeysStates>& MouseKeysState,
  const std::vector<Render::WindowsManager::BindsEngine::EnumMouseTable>& MouseKeys,
  Render::WindowsManager::Window* window) {

  const auto binds = World::GetBinds();

  binds->emplace_back(std::unique_ptr<Render::WindowsManager::BindsEngine::Bind>
  (new Render::WindowsManager::BindsEngine::Bind()));

  binds->back().get()->Create(
    Operations,
    {},
    {},
    MouseKeysState,
    MouseKeys,
    {},
    window);
  Logger::Logger::LogInfo("Mouse button bind created");

  return binds->back().get();
}

Render::WindowsManager::BindsEngine::Bind* Core::Factory::CreateMouseSensorBind(
  const std::vector<std::function<void(void)>>& Operations,
  const std::vector<Render::WindowsManager::BindsEngine::EnumMouseSensorStates>& MouseSensorState,
  Render::WindowsManager::Window* window) {

  const auto binds = World::GetBinds();

  binds->emplace_back(std::unique_ptr<Render::WindowsManager::BindsEngine::Bind>
  (new Render::WindowsManager::BindsEngine::Bind()));

  binds->back().get()->Create(Operations, {}, {}, {}, {}, MouseSensorState, window);

  Logger::Logger::LogInfo("Mouse sensor bind created");

  return binds->back().get();
}

Render::WindowsManager::BindsEngine::Bind* Core::Factory::CreateKeyboardBind(
  const std::vector<std::function<void(void)>>& Operations,
  const std::vector<Render::WindowsManager::BindsEngine::EnumKeyboardKeysStates>& KeysState,
  const std::vector<Render::WindowsManager::BindsEngine::EnumKeyboardTable>& KeyboardKeys,
  Render::WindowsManager::Window* window) {

  const auto binds = World::GetBinds();

  binds->emplace_back(std::unique_ptr<Render::WindowsManager::BindsEngine::Bind>
(new Render::WindowsManager::BindsEngine::Bind()));

  binds->back().get()->Create(
    Operations,
    KeysState,
    KeyboardKeys,
    {},
    {},
    {},
    window);

  Logger::Logger::LogInfo("Keyboard bind created");

  return binds->back().get();
}

void Core::Factory::RemoveBind(const Render::WindowsManager::BindsEngine::Bind* removedBind) {
  const auto binds = World::GetBinds();

  auto it = binds->begin();

  for (const auto& bind : *binds) {
    if (removedBind == bind.get()) {
      binds->erase(it);
      Logger::Logger::LogInfo("Bind removed");
      return;
    }
    std::advance(it, 1);
  }

  Logger::Logger::LogError("Bind does not exist: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
}
#endif



