#include "WindowsManager.h"

#include "GLFW/glfw3.h"

#include <cassert>
#include <iostream>

#if ANOMALY_ENGINE_INCLUDED
#include <Render/WinManager/AnomalyEngine/RenderEngine.h>
#endif

namespace Render::WindowsManager {
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
        printf("Info: Running against GLFW %i.%i.%i\n", major, minor, revision);
    }

    void WindowsManager::RenderLoop(std::vector<std::unique_ptr<Render::WindowsManager::Window>>* windows) {
#if ANOMALY_ENGINE_INCLUDED
        const auto rend = Render::AnomalyEngine::RenderEngine::GetInstance();
#endif

        for (auto& window : *windows) {
            glfwMakeContextCurrent(window->_window);

            if (window->_initialized == false)
                window->Init();

            glfwPollEvents();

#if ANOMALY_ENGINE_INCLUDED
            if (window != nullptr)
                rend->RenderLoop(*window);
#endif

            glfwSwapBuffers(window->_window);
        }
    }

}