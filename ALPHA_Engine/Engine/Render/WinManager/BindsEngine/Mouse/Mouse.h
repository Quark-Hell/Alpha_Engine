#pragma once
#include <Core/Math/Vectors.h>
#include <GLFW/glfw3.h>
#include "MouseSensors.h"

namespace Render::WindowsManager::BindsEngine {

class Mouse {
private:
    Core::Vector2 _previousMousePos;
    Core::Vector2 _currentMousePos;
    Core::Vector2 _mouseDelta;

private:
    MouseKey _leftButton{ GLFW_MOUSE_BUTTON_LEFT };
    MouseKey _rightButton{ GLFW_MOUSE_BUTTON_RIGHT };
    MouseKey _middleButton{ GLFW_MOUSE_BUTTON_MIDDLE };

    MouseKey _firstExtraButton{ GLFW_MOUSE_BUTTON_4 };
    MouseKey _secondExtraButton{ GLFW_MOUSE_BUTTON_5 };

    EnumMouseSensorStates MoveSensorState = UnknownState;

    MouseKey* Buttons[5] = {
        &_leftButton, &_rightButton,
        &_middleButton, &_firstExtraButton,
        &_secondExtraButton
    };

private:
    friend class InputSystem;

public:
    Core::Vector2 GetMousePos();
    Core::Vector2 GetMouseDelta();
    [[nodiscard]] bool IsMouseChangePosition() const;

    ~Mouse() = default;

private:
    Mouse() = default;
    void UpdateMouseState(GLFWwindow& window);
};

}