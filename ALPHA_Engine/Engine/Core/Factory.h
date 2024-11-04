#pragma once

#include <string>

namespace Register {
  class UserScript;
}

namespace Render {
  namespace WindowsManager {
    class Window;
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
};

}