#pragma once
#include <string>
#include <Anomaly/WinManager/AnomalyEngine/Components/Mesh.h>

namespace Register {
  class UserScript;
}

namespace AnomalyEngine {
  namespace WindowsManager {
    class Window;
  }
  namespace Render {
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

#if ANOMALY_ENGINE_INCLUDED
public:
  static AnomalyEngine::WindowsManager::Window* CreateWindow(int width, int height, const char* title);

  static AnomalyEngine::Render::Camera* CreateCamera(float fov = 90,float aspect = 1,float zNear = 0.1f,float zFar = 300);
  static bool RemoveCamera(const AnomalyEngine::Render::Camera* camera);

  static AnomalyEngine::Render::Mesh* CreateMesh();
  static AnomalyEngine::Render::Mesh* CreateMesh(const std::string& path);
#endif
};

}