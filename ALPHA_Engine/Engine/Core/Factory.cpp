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
Register::UserScript& Core::Factory::CreateUserScript() {
  World::GetUserScripts()->push_back(std::unique_ptr<Register::UserScript>(new Register::UserScript()));
  return *World::GetUserScripts()->back().get();
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
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

void Core::Factory::CreateWindow(int width, int height, const char* title) {
  using namespace AnomalyEngine::WindowsManager;
  WindowsManager& WinMan = WindowsManager::GetInstance();

  if (WinMan._initialized == false) {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
      glfwTerminate();
      assert("Cannot init GLFW Window");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glEnable(GL_MULTISAMPLE);

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    WinMan._initialized = true;

  }

  auto windows = Core::World::GetWindows();
  auto* wm = new Window(width,height, title);

  windows->push_back(std::unique_ptr<Window>(wm));
}

AnomalyEngine::Render::Camera& Core::Factory::CreateCamera() {
  auto camera = new AnomalyEngine::Render::Camera();

  auto cameras = World::GetCameras();
  cameras->push_back(std::unique_ptr<AnomalyEngine::Render::Camera>(camera));

  return *camera;
}

bool Core::Factory::RemoveCamera(AnomalyEngine::Render::Camera* camera) {
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



