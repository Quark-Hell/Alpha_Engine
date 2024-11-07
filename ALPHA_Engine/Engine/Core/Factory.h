#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <functional>

namespace Register {
  class UserScript;
}

namespace Render {
  namespace WindowsManager {
    class Window;
    namespace BindsEngine {
      enum class EnumKeyboardTable : uint16_t;
      class Bind;
      enum EnumKeyStates : int16_t;
      enum EnumMouseSensorStates : uint8_t;
    }
  }

  namespace AnomalyEngine::Components {
    class Mesh;
    class Camera;
  }
}

namespace Core {

class Object;
class Component;

class Factory {
    public:
      ~Factory();

    private:
      Factory();

public:
  static bool RemoveObject(const Core::Object* object);
  static Core::Object* CreateObject();

#if USER_SCRIPTS_REGISTER_INCLUDED
public:
  static bool RemoveUserScript(const Register::UserScript* object);
  static Register::UserScript* CreateUserScript();
  static Register::UserScript* CreateUserScript(Register::UserScript* script);
#endif

#if RENDER_INCLUDED
public:
  static Render::WindowsManager::Window* CreateWindow(int width, int height, const char* title);
#endif

#if ANOMALY_ENGINE_INCLUDED
  static Render::AnomalyEngine::Components::Camera* CreateCamera(float fov = 90,float aspect = 1,float zNear = 0.1f,float zFar = 3000);
  static bool RemoveCamera(const Render::AnomalyEngine::Components::Camera* camera);

  static Render::AnomalyEngine::Components::Mesh* CreateMesh();
  static Render::AnomalyEngine::Components::Mesh* CreateMesh(const std::string& path);
#endif

#if BINDS_ENGINE_INCLUDED
  static Render::WindowsManager::BindsEngine::Bind* CreateGeneralBind();

  static Render::WindowsManager::BindsEngine::Bind* CreateMouseButtonsBind(
    const std::vector<std::function<void(void)>>& Operations,
    const std::vector<Render::WindowsManager::BindsEngine::EnumKeyStates>& MouseKeysState,
    const std::vector<uint8_t>& MouseKeys,
    Render::WindowsManager::Window* window);

  static Render::WindowsManager::BindsEngine::Bind* CreateMouseSensorBind(
    const std::vector<std::function<void(void)>>& Operations,
    const Render::WindowsManager::BindsEngine::EnumMouseSensorStates MouseSensorState,
    Render::WindowsManager::Window* window);

  static Render::WindowsManager::BindsEngine::Bind* CreateKeyboardBind(
    const std::vector<std::function<void(void)>>& Operations,
    const std::vector<Render::WindowsManager::BindsEngine::EnumKeyStates>& KeysState,
    const std::vector<Render::WindowsManager::BindsEngine::EnumKeyboardTable>& KeyboardKeys,
    Render::WindowsManager::Window* window);

  static void RemoveBind(const Render::WindowsManager::BindsEngine::Bind* removedBind);
#endif
};

}