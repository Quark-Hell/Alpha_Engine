#include "WindowsManager.h"

#include <GLEW/glew.h>
#include <GL/gl.h>
#include "GLFW/glfw3.h"

#include  <cassert>

namespace AnomalyEngine::WindowsManager {
    WindowsManager::WindowsManager() = default;
    WindowsManager::~WindowsManager() = default;

    WindowsManager* WindowsManager::GetInstance() {
        auto* winMan = new WindowsManager();
        return winMan;
    }

    void WindowsManager::Init() {
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
        {
            assert("Cannot init GLFW Window");
            glfwTerminate();
        }
    }

}