#include "WindowsManager.h"

#include "Window.h"
#include "WindowsBuffer.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "Core/Logger/Logger.h"

namespace WindowsManager {

    WindowsManager::WindowsManager() : System({"WindowsBuffer"}, 10000) {
        if (!glfwInit()) {
            Core::Logger::LogCritical("Glfw does not inited: " + __LOGERROR__);
            abort();
        }
    };

    void WindowsManager::EntryPoint(std::vector<Core::SystemData*>& data) {
        auto* buffer = reinterpret_cast<WindowsBuffer*>(data[0]);

        for (size_t i = 0; i < buffer->GetAllData().size(); i++) {
            auto& component = buffer->GetData(i);

            if (glfwGetWindowAttrib(component._window, GLFW_ICONIFIED) == GLFW_TRUE) {
                continue;
            }
            if (glfwGetWindowAttrib(component.GetGLFWwindow(), GLFW_FOCUSED)) {
                buffer->_focusedWindow = &component;
            }

            glfwMakeContextCurrent(component._window);

            glfwSwapBuffers(component._window);
        }
        glfwPollEvents();
    }
}