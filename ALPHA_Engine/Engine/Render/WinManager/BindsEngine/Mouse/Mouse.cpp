#include "Mouse.h"
#include <GLFW/glfw3.h>
#include "Render/WinManager/BindsEngine/GeneralSensors.h"

namespace Render::WindowsManager::BindsEngine {
    void Mouse::UpdateMouseState() {
        double xPos, yPos;
        const auto window = glfwGetCurrentContext();
        glfwGetCursorPos(window, &xPos, &yPos);

        Mouse::_previousMousePos = Mouse::_currentMousePos;
        Mouse::_currentMousePos = {static_cast<float>(xPos), static_cast<float>(yPos)};

        Mouse::_mouseDelta = Core::Vector2{_currentMousePos - _previousMousePos};

        if (Mouse::_mouseDelta != Core::Vector2{0, 0}) {
            if (Mouse::MoveSensorState & MouseNotMoved || Mouse::MoveSensorState & MouseEndMoved) {
                Mouse::MoveSensorState = MouseStartMoved;
            } else if (Mouse::MoveSensorState & MouseStartMoved) {
                Mouse::MoveSensorState = MouseKeepMoved;
            }
        } else {
            if (Mouse::MoveSensorState & MouseKeepMoved || Mouse::MoveSensorState & MouseStartMoved) {
                Mouse::MoveSensorState = MouseEndMoved;
            } else {
                Mouse::MoveSensorState = MouseNotMoved;
            }
        }

        //Update mouse buttons state
        for (size_t i = 0; i < 5; i++) {
            if (glfwGetMouseButton(window, Buttons[i]->KEY)) {
                if (Buttons[i]->KeyState & EnumKeyStates::KeyNotPressed) {
                    Buttons[i]->KeyState = static_cast<EnumKeyStates>(KeyPressed | KeyHold);
                } else if (Buttons[i]->KeyState & EnumKeyStates::KeyPressed) {
                    Buttons[i]->KeyState = KeyHold;
                }
            } else {
                if (Buttons[i]->KeyState & EnumKeyStates::KeyHold || Buttons[i]->KeyState & EnumKeyStates::KeyPressed ||
                    Buttons[i]->KeyState & (EnumKeyStates) (KeyPressed | KeyHold)) {
                    Buttons[i]->KeyState = KeyReleased;
                    continue;
                }
                Buttons[i]->KeyState = KeyNotPressed;
            }
        }
    }

    Core::Vector2 Mouse::GetMouseDelta() {
        return _mouseDelta;
    }

    Core::Vector2 Mouse::GetMousePos() {
        return _currentMousePos;
    }

    bool Mouse::IsMouseChangePosition() const {
        if (Mouse::_mouseDelta == Core::Vector2{0, 0}) {
            return false;
        }
        return true;
    }
}
