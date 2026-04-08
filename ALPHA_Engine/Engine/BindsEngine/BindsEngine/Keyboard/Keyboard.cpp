#include "Keyboard.h"
#include "KeyboardSensors.h"

#include <GLFW/glfw3.h>

#include "Core/World.h"
#include "WindowsManager/Buffers/WindowsBuffer.h"

namespace BindsEngine {
    KeyboardSystem::KeyboardSystem(size_t order)  : System({"KeyboardSensorsBuffer", "WindowsBuffer"}, order) {};

    void KeyboardSystem::EntryPoint(std::vector<Core::SystemData*>& data) {
        if (data[0] == nullptr || data[1] == nullptr) {
            Core::Logger::LogError("Buffer was null: " + __LOGERROR__);
            return;
        }

        auto* keysData = reinterpret_cast<KeyboardSensors*>(data[0]);
        const auto* focusedWindow = reinterpret_cast<WindowsManager::WindowsBuffer*>(data[1]);

        WindowsManager::Window* window = focusedWindow->GetFocusedWindow();
        if (window == nullptr) {
            Core::Logger::LogWarning("Window was null");
            return;
        }
        GLFWwindow* glfwWindow = window->GetGLFWwindow();
        if (glfwWindow == nullptr) {
            Core::Logger::LogError("GLFW window was null: " + __LOGERROR__);
            return;
        }

        for (const auto& it: keysData->_data) {
            if (glfwGetKey(glfwWindow, static_cast<uint16_t>(it->KEY))) {
                if (it->KeyState == EnumKeyboardKeysStates::KeyNotPressed) {
                    it->KeyState = EnumKeyboardKeysStates::KeyPressed;
                } else if (it->KeyState == EnumKeyboardKeysStates::KeyPressed) {
                    it->KeyState = EnumKeyboardKeysStates::KeyHold;
                }
            } else {
                if (it->KeyState == EnumKeyboardKeysStates::KeyHold || it->KeyState == EnumKeyboardKeysStates::KeyPressed) {
                    it->KeyState = EnumKeyboardKeysStates::KeyReleased;
                    continue;
                }
                it->KeyState = EnumKeyboardKeysStates::KeyNotPressed;
            }
        }
    }
}
