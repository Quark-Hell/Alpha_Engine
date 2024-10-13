#pragma once
#include <list>
#include <memory>

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
  static Core::Object& CreateObject();

#if USER_SCRIPTS_REGISTER_INCLUDED
public:
  static bool RemoveUserScript(const Register::UserScript* object);
  static Register::UserScript& CreateUserScript();
  static Register::UserScript* CreateUserScript(Register::UserScript* script);
#endif

#if ANOMALY_ENGINE_INCLUDED
public:
  static void CreateWindow(int width, int height, const char* title);

  static AnomalyEngine::Render::Camera& CreateCamera();
  static bool RemoveCamera(AnomalyEngine::Render::Camera* camera);
#endif
};

}