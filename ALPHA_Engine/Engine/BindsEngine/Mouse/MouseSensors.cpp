#include "MouseSensors.h"

#include <GLFW/glfw3.h>

namespace BindsEngine {
    MouseSensors::MouseSensors() : Core::TSystemData<MouseKey>("MouseSensorsBuffer"){
        _data.reserve(8);

        _data.emplace_back(std::make_unique<MouseKey>(GLFW_MOUSE_BUTTON_1));
        _data.emplace_back(std::make_unique<MouseKey>(GLFW_MOUSE_BUTTON_2));
        _data.emplace_back(std::make_unique<MouseKey>(GLFW_MOUSE_BUTTON_3));
        _data.emplace_back(std::make_unique<MouseKey>(GLFW_MOUSE_BUTTON_4));
        _data.emplace_back(std::make_unique<MouseKey>(GLFW_MOUSE_BUTTON_5));
        _data.emplace_back(std::make_unique<MouseKey>(GLFW_MOUSE_BUTTON_6));
        _data.emplace_back(std::make_unique<MouseKey>(GLFW_MOUSE_BUTTON_7));
        _data.emplace_back(std::make_unique<MouseKey>(GLFW_MOUSE_BUTTON_8));

        _mouseSensorState = EnumMouseSensorStates::MouseNotMoved;
    }

    EnumMouseKeysStates MouseSensors::GetKeyState(const EnumMouseTable key) const {
        for (const auto& it : _data) {
            if (it->KEY == key) { return it->KeyState; }
        }

        return EnumMouseKeysStates::KeyNotPressed;
    }

    EnumMouseSensorStates MouseSensors::GetSensorState() const {
        return _mouseSensorState;
    }

    Core::Vector2 MouseSensors::GetMouseDelta() const {
        return _mouseDelta;
    }

    Core::Vector2 MouseSensors::GetMousePos() const {
        return _currentMousePos;
    }

    bool MouseSensors::IsMouseChangePosition() const {
        if (_mouseDelta == Core::Vector2{0, 0}) {
            return false;
        }
        return true;
    }
}
