#include "WindowsManager.h"

#include <GLEW/glew.h>
#include <GL/gl.h>
#include "GLFW/glfw3.h"

#include  <cassert>
#include <iostream>

namespace AnomalyEngine::WindowsManager {
    WindowsManager::WindowsManager() = default;
    WindowsManager::~WindowsManager() = default;

    WindowsManager* WindowsManager::GetInstance() {
        auto* winMan = new WindowsManager();
        return winMan;
    }

    void WindowsManager::Init() {
        if (!glfwInit()) {
            std::cout << "glfw does not inited" << std::endl;
            abort();
        }

        int major, minor, revision;
        glfwGetVersion(&major, &minor, &revision);
        printf("Running against GLFW %i.%i.%i\n", major, minor, revision);
    }

}