#include "WindowsManager.h"

#include "Window.h"
#include "GLFW/glfw3.h"
#include "Logger/Logger.h"

#if ANOMALY_ENGINE_INCLUDED
#include <Render/WinManager/AnomalyEngine/RenderEngine.h>
#endif

#if BINDS_ENGINE_INCLUDED
#include "BindsEngine/InputSystem.h"
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
            Logger::Logger::LogCritical("Glfw does not inited: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            abort();
        }
    }

    void WindowsManager::RenderLoop(std::vector<std::unique_ptr<Render::WindowsManager::Window>>* windows) {
#if ANOMALY_ENGINE_INCLUDED
        const auto rend = Render::WindowsManager::AnomalyEngine::RenderEngine::GetInstance();
#endif

        for (auto& window : *windows) {
            if (glfwGetWindowAttrib(window->_window, GLFW_ICONIFIED) == GLFW_TRUE) {
                continue;
            }

            glfwMakeContextCurrent(window->_window);

#if BINDS_ENGINE_INCLUDED
            if (glfwGetWindowAttrib(window->_window, GLFW_FOCUSED)) {
                const auto bind = Render::WindowsManager::BindsEngine::InputSystem::GetInstance();
                bind->IO_Events(window.get());
            }
#endif

#if ANOMALY_ENGINE_INCLUDED
            if (window != nullptr)
                rend->RenderLoop(*window);
#endif

            glfwSwapBuffers(window->_window);
        }
        glfwPollEvents();
    }
}