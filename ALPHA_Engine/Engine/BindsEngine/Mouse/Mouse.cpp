#include "Mouse.h"

#include <GLFW/glfw3.h>
#include "WindowsManager/Components/Window.h"
#include "WindowsManager/Buffers/WindowsBuffer.h"

#include "MouseSensors.h"
#include "Core/Math/glmMath.h"

namespace BindsEngine {

    MouseSystem::MouseSystem(size_t order) : System({"MouseSensorsBuffer", "WindowsBuffer"}, order) {};

    void MouseSystem::EntryPoint(std::vector<Core::SystemData*>& data) {
        if (data[0] == nullptr || data[1] == nullptr) {
            Core::Logger::LogError("Data was null: " + __LOGERROR__);
            return;
        }

        auto* mouseSensors = reinterpret_cast<MouseSensors*>(data[0]);
        auto* windowsBuffer = reinterpret_cast<WindowsManager::WindowsBuffer*>(data[1]);

        double xPos, yPos;
        const WindowsManager::Window* focusedWindow = windowsBuffer->GetFocusedWindow();
        if (focusedWindow == nullptr) {
            return;
        }
        glfwGetCursorPos(focusedWindow->GetGLFWwindow(), &xPos, &yPos);

        mouseSensors->_previousMousePos = glm::vec2(mouseSensors->_currentMousePos.x, mouseSensors->_currentMousePos.y);
        mouseSensors->_currentMousePos = glm::vec2(static_cast<float>(xPos), static_cast<float>(yPos));

        mouseSensors->_mouseDelta = mouseSensors->_currentMousePos - mouseSensors->_previousMousePos;

        if (mouseSensors->_mouseDelta != glm::vec2 (0, 0)) {
            if (mouseSensors->_mouseSensorState == EnumMouseSensorStates::MouseNotMoved || mouseSensors->_mouseSensorState == EnumMouseSensorStates::MouseEndMoved) {
                mouseSensors->_mouseSensorState = EnumMouseSensorStates::MouseStartMoved;
            } else if (mouseSensors->_mouseSensorState == EnumMouseSensorStates::MouseStartMoved) {
                mouseSensors->_mouseSensorState = EnumMouseSensorStates::MouseKeepMoved;
            }
        } else {
            if (mouseSensors->_mouseSensorState == EnumMouseSensorStates::MouseKeepMoved || mouseSensors->_mouseSensorState == EnumMouseSensorStates::MouseStartMoved) {
                mouseSensors->_mouseSensorState = EnumMouseSensorStates::MouseEndMoved;
            } else {
                mouseSensors->_mouseSensorState = EnumMouseSensorStates::MouseNotMoved;
            }
        }

        for (const auto& key : mouseSensors->_data) {
            if (glfwGetMouseButton(focusedWindow->GetGLFWwindow(), static_cast<int>(key->KEY))) {
                if (key->KeyState == EnumMouseKeysStates::KeyNotPressed) {
                    key->KeyState = EnumMouseKeysStates::KeyPressed;
                }
                else if (key->KeyState == EnumMouseKeysStates::KeyPressed) {
                    key->KeyState = EnumMouseKeysStates::KeyHold;
                }
            }
            else {
                if (key->KeyState == EnumMouseKeysStates::KeyHold || key->KeyState == EnumMouseKeysStates::KeyPressed) {
                    key->KeyState = EnumMouseKeysStates::KeyReleased;
                    continue;
                }
                key->KeyState = EnumMouseKeysStates::KeyNotPressed;
            }
        }
    }
}
