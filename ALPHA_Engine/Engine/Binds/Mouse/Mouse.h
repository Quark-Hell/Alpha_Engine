#pragma once
#include "MousePos.h"
#include "MouseSensors.h"

namespace BindsEngine {

class Mouse {
private:
    MousePos _previousMousePos;
    MousePos _currentMousePos;
    MousePos _mouseDelta;

private:
    MouseKey _leftButton{ GLFW_MOUSE_BUTTON_LEFT };
    MouseKey _rightButton{ GLFW_MOUSE_BUTTON_RIGHT };
    MouseKey _middleButton{ GLFW_MOUSE_BUTTON_MIDDLE };

    MouseKey _firstExtraButton{ GLFW_MOUSE_BUTTON_4 };
    MouseKey _secondExtraButton{ GLFW_MOUSE_BUTTON_5 };

    EnumMouseSensorStates MoveSensorState;

    MouseKey* Buttons[5] = {
        &_leftButton, &_rightButton,
        &_middleButton, &_firstExtraButton,
        &_secondExtraButton
    };

private:
    friend class InputSystem;

public:
    MousePos GetMousePos();
    MousePos GetMouseDelta();
    bool IsMouseChangePosition();

    Mouse();
    ~Mouse();

private:
    void UpdateMouseState(GLFWwindow& window);
};

}