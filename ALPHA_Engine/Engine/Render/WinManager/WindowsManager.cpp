#include "WindowsManager.h"

#include "Window.h"
#include "WindowsBuffer.h"

#include "GLFW/glfw3.h"
#include "Logger/Logger.h"

#if ANOMALY_ENGINE_INCLUDED
#include <Render/WinManager/AnomalyEngine/RenderEngine.h>
#endif

#if BINDS_ENGINE_INCLUDED
#include "BindsEngine/InputSystem.h"
#endif

namespace Render::WindowsManager {

    WindowsManager::WindowsManager() : System({"WindowsBuffer"}, 400) {
        if (!glfwInit()) {
            Logger::Logger::LogCritical("Glfw does not inited: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            abort();
        }
    };

    WindowsManager* WindowsManager::GetInstance() {
        static WindowsManager winMan;
        return &winMan;
    }

    void WindowsManager::EntryPoint(Core::SystemData& data) {
        auto* buffer = dynamic_cast<WindowsBuffer*>(&data);
        if (buffer == nullptr) {
            return;
        }

        for (size_t i = 0; i < buffer->GetAllData().size(); i++) {
            auto& component = buffer->GetData(i);

#if ANOMALY_ENGINE_INCLUDED
            const auto rend = Render::WindowsManager::AnomalyEngine::RenderEngine::GetInstance();
#endif

            if (glfwGetWindowAttrib(component._window, GLFW_ICONIFIED) == GLFW_TRUE) {
                continue;
            }

            glfwMakeContextCurrent(component._window);

#if BINDS_ENGINE_INCLUDED
            if (glfwGetWindowAttrib(component._window, GLFW_FOCUSED)) {
                const auto bind = Render::WindowsManager::BindsEngine::InputSystem::GetInstance();
                bind->IO_Events(&component);
            }
#endif
#if ANOMALY_ENGINE_INCLUDED
            rend->RenderLoop(component);
#endif
            glfwSwapBuffers(component._window);
        }
        glfwPollEvents();
    }
}