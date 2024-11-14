#include "Factory.h"

#include <Render/WinManager/AnomalyEngine/Components/DirectLight.h>

#include "EngineConfig.h"

#include "World.h"
#include "Object.h"
#include "Components/Component.h"

bool Core::Factory::RemoveObject(const Core::Object* object) {
  const auto list = World::GetObjects();
  auto it = std::begin(*list);

  for (size_t i = 0; i < World::GetObjects()->size(); ++i) {
    if (it->get() == &object[i]) {
      std::cout << "Info: Removing object " << std::endl;
      World::GetObjects()->erase(it);
      std::cout << "Info: Removed object " << std::endl;
      return true;
    }
    std::advance(it, 1);
  }

  std::cout << "Error: Object do not exist" << std::endl;
  return false;
}

Core::Object* Core::Factory::CreateObject() {
  World::GetObjects()->emplace_back(std::unique_ptr<Core::Object>(new Core::Object()));
  std::cout << "Info: Object created" << std::endl;
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
      std::cout << "Info: Removing user script" << std::endl;
      World::GetUserScripts()->erase(it);
      std::cout << "Info: Removed user script" << std::endl;
      return true;
    }
    std::advance(it, 1);
  }
  std::cout << "Error: User script cannot be removed" << std::endl;
  return false;
}

Register::UserScript* Core::Factory::CreateUserScript(Core::Component* script) {
  const auto src = dynamic_cast<Register::UserScript*>(script);
  if (src == nullptr) {
    std::cout << "Error: Argument is not a User Script type" << std::endl;
    return nullptr;
  }

  const auto userScripts = World::GetUserScripts();
  for (auto& it : *userScripts) {
    if (src == it.get()) {
      std::cout << "Error: User script already exist" << std::endl;
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

    std::cout << "Info: Created shared window" << std::endl;
  }
  else {
    windows->emplace_back(std::unique_ptr<Window>
(new Window(width,height, title,nullptr,nullptr)));

    std::cout << "Info: Window created" << std::endl;
  }

  return windows->back().get();
}
#endif

#if ANOMALY_ENGINE_INCLUDED
Render::AnomalyEngine::Components::Camera* Core::Factory::CreateCamera(const float fov, const float aspect, const float zNear, const float zFar) {
  const auto cameras = World::GetCameras();

  cameras->emplace_back(std::unique_ptr<Render::AnomalyEngine::Components::Camera>
    (new Render::AnomalyEngine::Components::Camera(fov, aspect, zNear, zFar)));

  std::cout << "Info: Camera created" << std::endl;
  return static_cast<Render::AnomalyEngine::Components::Camera*>(cameras->back().get());
}

bool Core::Factory::RemoveCamera(const Render::AnomalyEngine::Components::Camera* camera) {
  const auto list = World::GetCameras();
  auto it = std::begin(*list);

  for (size_t i = 0; i < World::GetCameras()->size(); ++i) {
    if (it->get() == &camera[i]) {
      std::cout << "Info: Removing camera" << std::endl;
      World::GetCameras()->erase(it);
      std::cout << "Info: Removed camera" << std::endl;
      return true;
    }
    std::advance(it, 1);
  }
  std::cout << "Error: Camera cannot be removed";
  return false;
}

Render::AnomalyEngine::Components::Mesh* Core::Factory::CreateMesh() {
  const auto meshes = World::GetMeshes();

  meshes->emplace_back(std::unique_ptr<Render::AnomalyEngine::Components::Mesh>
    (new Render::AnomalyEngine::Components::Mesh()));

  std::cout << "Info: Mesh created" << std::endl;

  return static_cast<Render::AnomalyEngine::Components::Mesh*>(meshes->back().get());
}

Render::AnomalyEngine::Components::Mesh* Core::Factory::CreateMesh(const std::string& path) {
  const auto meshes = World::GetMeshes();

  meshes->emplace_back(std::unique_ptr<Render::AnomalyEngine::Components::Mesh>
    (new Render::AnomalyEngine::Components::Mesh()));

  static_cast<Render::AnomalyEngine::Components::Mesh*>(meshes->back().get())->Create(path);
  std::cout << "Info: Mesh created" << std::endl;

  return static_cast<Render::AnomalyEngine::Components::Mesh*>(meshes->back().get());
}

Render::AnomalyEngine::Components::DirectLight *Core::Factory::CreateDirectLight(const Core::Vector3& direction) {
  const auto lights = World::GetDirectLights();

  lights->emplace_back(std::unique_ptr<Render::AnomalyEngine::Components::DirectLight>(new Render::AnomalyEngine::Components::DirectLight(direction)));

  std::cout << "Info: Direct light created" << std::endl;

  return static_cast<Render::AnomalyEngine::Components::DirectLight*>(lights->back().get());
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
    static_cast<Render::WindowsManager::BindsEngine::EnumMouseSensorStates>(1),
    window);
  std::cout << "Info: Mouse button bind created" << std::endl;

  return binds->back().get();
}

Render::WindowsManager::BindsEngine::Bind* Core::Factory::CreateMouseSensorBind(
  const std::vector<std::function<void(void)>>& Operations,
  const Render::WindowsManager::BindsEngine::EnumMouseSensorStates MouseSensorState,
  Render::WindowsManager::Window* window) {

  const auto binds = World::GetBinds();

  binds->emplace_back(std::unique_ptr<Render::WindowsManager::BindsEngine::Bind>
  (new Render::WindowsManager::BindsEngine::Bind()));

  binds->back().get()->Create(Operations, {}, {}, {}, {}, MouseSensorState, window);
  std::cout << "Info: Mouse sensor bind created" << std::endl;

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
    static_cast<Render::WindowsManager::BindsEngine::EnumMouseSensorStates>(0),
    window);
  std::cout << "Info: Keyboard bind created" << std::endl;

  return binds->back().get();
}

void Core::Factory::RemoveBind(const Render::WindowsManager::BindsEngine::Bind* removedBind) {
  const auto binds = World::GetBinds();

  auto it = binds->begin();

  for (const auto& bind : *binds) {
    if (removedBind == bind.get()) {
      binds->erase(it);
      std::cout << "Info: Bind removed" << std::endl;
      return;
    }
    std::advance(it, 1);
  }

  std::cout << "Error: Bind does not exist" << std::endl;
}
#endif



