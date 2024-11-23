#include "WindowsManager.h"

#include "Window.h"
#include "WindowsBuffer.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "Core/Logger/Logger.h"

#if ANOMALY_ENGINE_INCLUDED
#include <Render/WinManager/AnomalyEngine/RenderEngine.h>
#endif

#if BINDS_ENGINE_INCLUDED
#include "BindsEngine/InputSystem.h"
#endif

namespace Render::WindowsManager {

    WindowsManager::WindowsManager() : System({"WindowsBuffer"}, 400) {
        if (!glfwInit()) {
            Core::Logger::LogCritical("Glfw does not inited: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            abort();
        }
    };

    void WindowsManager::EntryPoint(std::vector<Core::SystemData*>& data) {
        auto* buffer = reinterpret_cast<WindowsBuffer*>(data[0]);

        for (size_t i = 0; i < buffer->GetAllData().size(); i++) {
            auto& component = buffer->GetData(i);

#if ANOMALY_ENGINE_INCLUDED
            const auto rend = Render::WindowsManager::AnomalyEngine::RenderEngine::GetInstance();
#endif

            if (glfwGetWindowAttrib(component._window, GLFW_ICONIFIED) == GLFW_TRUE) {
                continue;
            }
            if (glfwGetWindowAttrib(const_cast<GLFWwindow*>(component.GetGLFWwindow()), GLFW_FOCUSED)) {
                buffer->_focusedWindow = &component;
            }

            glfwMakeContextCurrent(component._window);

#if ANOMALY_ENGINE_INCLUDED
            rend->RenderLoop(component);
#endif
            glfwSwapBuffers(component._window);
        }
        glfwPollEvents();
    }
}