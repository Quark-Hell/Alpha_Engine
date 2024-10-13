#pragma once
#include <list>
#include <memory>

namespace Register {
  class UserScript;
}

namespace AnomalyEngine::WindowsManager {
      class Window;
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

public:
  static bool RemoveUserScript(const Register::UserScript* object);
  static Register::UserScript& CreateUserScript();
  static Register::UserScript* CreateUserScript(Register::UserScript* script);

  static void CreateWindow();

};

}