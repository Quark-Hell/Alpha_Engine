#include "Factory.h"
#include <cassert>

#include "EngineConfig.h"

#include "World.h"
#include "Object.h"

bool Core::Factory::RemoveObject(const Core::Object* object) {
  const auto list = World::GetObjects();
  auto it = std::begin(*list);

  for (size_t i = 0; i < World::GetObjects()->size(); ++i) {
    if (it->get() == &object[i]) {
      std::cout << "Removing object " << std::endl;
      World::GetObjects()->erase(it);
      std::cout << "Removed object " << std::endl;
      return true;
    }
    std::advance(it, 1);
  }

  assert("Object cannot be removed");
  return false;
}

Core::Object& Core::Factory::CreateObject() {
  World::GetObjects()->push_back(std::unique_ptr<Core::Object>(new Core::Object()));
  return *World::GetObjects()->back().get();
}

bool Core::Factory::RemoveUserScript(const Register::UserScript* script) {
  const auto list = World::GetUserScripts();
  auto it = std::begin(*list);
  for (size_t i = 0; i < World::GetObjects()->size(); ++i) {
    if (it->get() == &script[i]) {
      std::cout << "Removing user script" << std::endl;
      World::GetUserScripts()->erase(it);
      std::cout << "Removed user script" << std::endl;
      return true;
    }
    std::advance(it, 1);
  }
  assert("User script cannot be removed");
  return false;
}

#if USER_SCRIPTS_REGISTER_INCLUDED
Register::UserScript* Core::Factory::CreateUserScript() {
  World::GetUserScripts()->push_back(std::unique_ptr<Register::UserScript>(new Register::UserScript()));
  return World::GetUserScripts()->back().get();
}
Register::UserScript* Core::Factory::CreateUserScript(Register::UserScript* script) {
  const auto list = World::GetUserScripts();
  auto it = std::begin(*list);
  for (size_t i = 0; i < World::GetUserScripts()->size(); ++i) {
    if (it->get() == &script[i]) {
      assert("User script already exist");
    }
    std::advance(it, 1);
  }
  World::GetUserScripts()->push_back(std::unique_ptr<Register::UserScript>(script));
  return World::GetUserScripts()->back().get();
}
#endif

#if ANOMALY_ENGINE_INCLUDED

#include <GLEW/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

AnomalyEngine::WindowsManager::Window* Core::Factory::CreateWindow(const int width, const int height, const char* title) {
  using namespace AnomalyEngine::WindowsManager;

  const auto windows = Core::World::GetWindows();

  windows->push_back(std::unique_ptr<Window>
    (new Window(width,height, title)));

  return windows->back().get();
}

AnomalyEngine::Render::Camera* Core::Factory::CreateCamera(const float fov, const float aspect, const float zNear, const float zFar) {
  const auto cameras = World::GetCameras();

  cameras->push_back(std::unique_ptr<AnomalyEngine::Render::Camera>
    (new AnomalyEngine::Render::Camera(fov, aspect, zNear, zFar)));

  std::cout << "Camera created" << std::endl;
  return cameras->back().get();
}

bool Core::Factory::RemoveCamera(const AnomalyEngine::Render::Camera* camera) {
  const auto list = World::GetCameras();
  auto it = std::begin(*list);

  for (size_t i = 0; i < World::GetCameras()->size(); ++i) {
    if (it->get() == &camera[i]) {
      std::cout << "Removing camera" << std::endl;
      World::GetCameras()->erase(it);
      std::cout << "Removed camera" << std::endl;
      return true;
    }
    std::advance(it, 1);
  }
  assert("Camera cannot be removed");
  return false;
}
#endif



