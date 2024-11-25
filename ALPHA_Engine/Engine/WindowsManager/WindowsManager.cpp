#include "WindowsManager.h"

#include <AnomalyEngine/Buffers/CamerasBuffer.h>
#include <AnomalyEngine/Components/Camera.h>
#include <Core/World.h>

#include "Window.h"
#include "WindowsBuffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Logger/Logger.h"

namespace WindowsManager {
    WindowsManager::WindowsManager() : System({"WindowsBuffer", "CamerasBuffer"}, 10000) {
        if (!glfwInit()) {
            Core::Logger::LogCritical("Glfw does not inited: " + __LOGERROR__);
            abort();
        }
    };

    void WindowsManager::EntryPoint(std::vector<Core::SystemData*>& data) {
        auto* buffer = reinterpret_cast<WindowsBuffer*>(data[0]);


        for (size_t i = 0; i < buffer->GetAllData().size(); i++) {
            auto& component = buffer->GetData(i);

            if (glfwWindowShouldClose(component._window)) {
                if (buffer->_focusedWindow->_window == component._window) {
                    buffer->_focusedWindow = nullptr;
                }
                //Delete active window from camera that used it
                if (data[1] != nullptr) {
                    auto camerabuffer = reinterpret_cast<AnomalyEngine::CamerasBuffer*>(data[1]);
                    for (size_t j = 0; j < camerabuffer->GetAllData().size(); j++) {
                        auto& camera = camerabuffer->GetData(j);
                        if (camera._window == component._window) {
                            camera._window = nullptr;
                        }
                    }
                }

                buffer->DestroyData(i);
                if (buffer->GetAllData().empty()) {
                    Core::World::CloseGame();
                }
            }
            else {
                if (glfwGetWindowAttrib(component._window, GLFW_ICONIFIED) == GLFW_TRUE) {
                    continue;
                }
                if (glfwGetWindowAttrib(component.GetGLFWwindow(), GLFW_FOCUSED)) {
                    buffer->_focusedWindow = &component;
                }

                glfwMakeContextCurrent(component._window);

                glfwSwapBuffers(component._window);
            }
        }
        glfwPollEvents();
    }
}