#include "Mouse.h"

#include <array>
#include <GLFW/glfw3.h>

namespace Render::WindowsManager::BindsEngine {

    EnumMouseKeysStates Mouse::GetKeyState(const EnumMouseTable key) {
        const auto mouse = MouseData::GetInstance();

        for (size_t i = 0; i < 99; i++) {
            if (mouse->Keys->at(i).KEY == key) { return mouse->Keys->at(i).KeyState; }
        }

        return EnumMouseKeysStates::KeyNotPressed;
    }

    EnumMouseSensorStates Mouse::GetSensorState() {
        const auto mouse = MouseData::GetInstance();
        return mouse->_mouseSensorState;
    }

    void Mouse::UpdateMouseState() {
        double xPos, yPos;
        const auto window = glfwGetCurrentContext();
        glfwGetCursorPos(window, &xPos, &yPos);

        const auto mouse = MouseData::GetInstance();

        mouse->_previousMousePos = mouse->_currentMousePos;
        mouse->_currentMousePos = {static_cast<float>(xPos), static_cast<float>(yPos)};

        mouse->_mouseDelta = Core::Vector2{mouse->_currentMousePos - mouse->_previousMousePos};

        if (mouse->_mouseDelta != Core::Vector2{0, 0}) {
            if (mouse->_mouseSensorState == EnumMouseSensorStates::MouseNotMoved || mouse->_mouseSensorState == EnumMouseSensorStates::MouseEndMoved) {
                mouse->_mouseSensorState = EnumMouseSensorStates::MouseStartMoved;
            } else if (mouse->_mouseSensorState == EnumMouseSensorStates::MouseStartMoved) {
                mouse->_mouseSensorState = EnumMouseSensorStates::MouseKeepMoved;
            }
        } else {
            if (mouse->_mouseSensorState == EnumMouseSensorStates::MouseKeepMoved || mouse->_mouseSensorState == EnumMouseSensorStates::MouseStartMoved) {
                mouse->_mouseSensorState = EnumMouseSensorStates::MouseEndMoved;
            } else {
                mouse->_mouseSensorState = EnumMouseSensorStates::MouseNotMoved;
            }
        }

        for (auto& key : *mouse->Keys) {
            if (glfwGetMouseButton(window, static_cast<int>(key.KEY))) {
                if (key.KeyState == EnumMouseKeysStates::KeyNotPressed) {
                    key.KeyState = EnumMouseKeysStates::KeyPressed;
                }
                else if (key.KeyState == EnumMouseKeysStates::KeyPressed) {
                    key.KeyState = EnumMouseKeysStates::KeyHold;
                }
            }
            else {
                if (key.KeyState == EnumMouseKeysStates::KeyHold || key.KeyState == EnumMouseKeysStates::KeyPressed) {
                    key.KeyState = EnumMouseKeysStates::KeyReleased;
                    continue;
                }
                key.KeyState = EnumMouseKeysStates::KeyNotPressed;
            }
        }
    }

    Core::Vector2 Mouse::GetMouseDelta() {
        const auto mouse = MouseData::GetInstance();
        return mouse->_mouseDelta;
    }

    Core::Vector2 Mouse::GetMousePos() {
        const auto mouse = MouseData::GetInstance();
        return mouse->_currentMousePos;
    }

    bool Mouse::IsMouseChangePosition() const {
        const auto mouse = MouseData::GetInstance();
        if (mouse->_mouseDelta == Core::Vector2{0, 0}) {
            return false;
        }
        return true;
    }
}
