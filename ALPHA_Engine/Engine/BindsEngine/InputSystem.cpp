#include "InputSystem.h"

#include "WindowsManager/Window.h"
#include "WindowsManager/WindowsBuffer.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "Binds.h"
#include "BindsBuffer.h"

#include "Keyboard/KeyboardSensors.h"
#include "Mouse/MouseSensors.h"

namespace BindsEngine {

    InputSystem::InputSystem() : System({"BindsBuffer", "WindowsBuffer", "MouseSensorsBuffer", "KeyboardSensorsBuffer"}, 220) {}

    void InputSystem::EntryPoint(std::vector<Core::SystemData*>& data) {
        if (data[0] == nullptr || data[1] == nullptr || data[2] == nullptr || data[3] == nullptr) {
            Core::Logger::LogError("Data buffer was null: " + __LOGERROR__);
        }

        auto* bindsBuffer = reinterpret_cast<BindsBuffer*>(data[0]);
        auto* windowsBuffer = reinterpret_cast<WindowsManager::WindowsBuffer*>(data[1]);
        auto* mouseSensorsBuffer = reinterpret_cast<MouseSensors*>(data[2]);
        auto* keyboardSensorsBuffer = reinterpret_cast<KeyboardSensors*>(data[3]);

        //Seek focused window
        const WindowsManager::Window* focusedWindow = windowsBuffer->GetFocusedWindow();
        if (focusedWindow == nullptr) {
            return;
        }

        glfwMakeContextCurrent(const_cast<GLFWwindow*>(focusedWindow->GetGLFWwindow()));

        //All values
        for (size_t i = 0; i < bindsBuffer->GetAllData().size(); i++) {

            auto& component = bindsBuffer->GetData(i);

            if (component.IsActive == false) { continue; }
            bool mark = true;

            //Keyboard statement check
            for (size_t j = 0; j < component._keyboardKeys.size(); j++)
            {
                const EnumKeyboardKeysStates state = keyboardSensorsBuffer->GetKeyState(component._keyboardKeys[j]);

                if (component._keyboardKeysState[j] != state) { mark = false; break; }
            }

            //Mouse button statement check
            for (size_t j = 0; j < component._mouseKeys.size(); j++)
            {
                EnumMouseKeysStates state = mouseSensorsBuffer->GetKeyState(component._mouseKeys[j]);

                if (component._mouseKeysState[j] != state) { mark = false; break; }
            }

            const EnumMouseSensorStates state = mouseSensorsBuffer->GetSensorState();

            //Check mouse sensor statement
            for (const auto& it : component._mouseSensorState) {
                if (it == EnumMouseSensorStates::Unknown && it != state) {
                    mark = false;
                    break;
                }
                else {
                    mark = true;
                    break;
                }
            }

            if (mark) { component.InvokeOperations(focusedWindow); }
        }
    }
}
