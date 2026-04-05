#include "WindowsManager.h"

#ifdef ANOMALY_ENGINE_INCLUDED
#include <AnomalyEngine/Buffers/CamerasBuffer.h>
#include <AnomalyEngine/Components/Camera.h>
#endif

#include <Core/World.h>

#include "WindowsManager/Components/Window.h"
#include "Buffers/WindowsBuffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Logger/Logger.h"

namespace WindowsManager {
    WindowsManager::WindowsManager(size_t order) : System({"WindowsBuffer", "CamerasBuffer"}, order) {
        if (!glfwInit()) {
            Core::Logger::LogCritical("Glfw does not inited: " + __LOGERROR__);
            abort();
        }
    };

    void WindowsManager::EntryPoint(std::vector<Core::SystemData*>& data) {
        auto* buffer = reinterpret_cast<WindowsBuffer*>(data[0]);


        for (size_t i = 0; i < buffer->GetAllData().size(); i++) {
            auto& window = buffer->GetData(i);

            if (glfwWindowShouldClose(window._window)) {
                if (buffer->_focusedWindow->_window == window._window) {
                    buffer->_focusedWindow = nullptr;
                }

                buffer->DestroyData(i);
                if (buffer->GetAllData().empty()) {
                    Core::World::CloseGame();
                }
            }
            else {
                if (glfwGetWindowAttrib(window._window, GLFW_ICONIFIED) == GLFW_TRUE) {
                    continue;
                }
                if (glfwGetWindowAttrib(window.GetGLFWwindow(), GLFW_FOCUSED)) {
                    buffer->_focusedWindow = &window;
                }

                glfwMakeContextCurrent(window._window);

                glfwSwapBuffers(window._window);
            }
        }
        glfwPollEvents();
    }
}