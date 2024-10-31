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
      std::cout << "Info: Removing object " << std::endl;
      World::GetObjects()->erase(it);
      std::cout << "Info: Removed object " << std::endl;
      return true;
    }
    std::advance(it, 1);
  }

  assert("Object cannot be removed");
  return false;
}

Core::Object* Core::Factory::CreateObject() {
  World::GetObjects()->push_back(std::unique_ptr<Core::Object>(new Core::Object()));
  std::cout << "Info: Object created" << std::endl;
  return World::GetObjects()->back().get();
}

bool Core::Factory::RemoveUserScript(const Register::UserScript* script) {
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
      std::cout << "Error: User script already exist" << std::endl;
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

Render::WindowsManager::Window* Core::Factory::CreateWindow(const int width, const int height, const char* title) {
  using namespace Render::WindowsManager;

  const auto windows = Core::World::GetWindows();
  size_t count = windows->size();

  if (count >= 1) {
    windows->push_back(std::unique_ptr<Window>
(new Window(width,height, title,nullptr,windows->at(0)->_window)));

    std::cout << "Info: Created shared window" << std::endl;
  }
  else {
    windows->push_back(std::unique_ptr<Window>
(new Window(width,height, title,nullptr,nullptr)));

    std::cout << "Info: Window created" << std::endl;
  }

  return windows->back().get();
}

Render::AnomalyEngine::Components::Camera* Core::Factory::CreateCamera(const float fov, const float aspect, const float zNear, const float zFar) {
  const auto cameras = World::GetCameras();

  cameras->push_back(std::unique_ptr<Render::AnomalyEngine::Components::Camera>
    (new Render::AnomalyEngine::Components::Camera(fov, aspect, zNear, zFar)));

  std::cout << "Info: Camera created" << std::endl;
  return cameras->back().get();
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
  assert("Camera cannot be removed");
  return false;
}

Render::AnomalyEngine::Components::Mesh* Core::Factory::CreateMesh() {
  const auto meshes = World::GetMeshes();

  meshes->push_back(std::unique_ptr<Render::AnomalyEngine::Components::Mesh>
    (new Render::AnomalyEngine::Components::Mesh()));

  std::cout << "Info: Mesh created" << std::endl;

  return meshes->back().get();
}

Render::AnomalyEngine::Components::Mesh* Core::Factory::CreateMesh(const std::string& path) {
  const auto meshes = World::GetMeshes();

  meshes->push_back(std::unique_ptr<Render::AnomalyEngine::Components::Mesh>
    (new Render::AnomalyEngine::Components::Mesh()));

  meshes->back().get()->Create(path);
  std::cout << "Info: Mesh created" << std::endl;

  return meshes->back().get();
}
#endif



