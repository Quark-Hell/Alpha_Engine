#pragma once
#include <Core/Math/Vectors.h>
#include "MouseSensors.h"

struct GLFWwindow;

namespace Render::WindowsManager::BindsEngine {
    class InputSystem;

    class Mouse {
    private:
        Core::Vector2 _previousMousePos;
        Core::Vector2 _currentMousePos;
        Core::Vector2 _mouseDelta;

    private:
        //GLFW_MOUSE_BUTTON_LEFT = 0
        //GLFW_MOUSE_BUTTON_RIGHT = 1
        //GLFW_MOUSE_BUTTON_MIDDLE = 2
        //GLFW_MOUSE_BUTTON_4 = 3
        //GLFW_MOUSE_BUTTON_5 = 4

        MouseKey _leftButton{0};
        MouseKey _rightButton{1};
        MouseKey _middleButton{2};

        MouseKey _firstExtraButton{3};
        MouseKey _secondExtraButton{4};

        EnumMouseSensorStates MoveSensorState = UnknownState;

        MouseKey *Buttons[5] = {
            &_leftButton, &_rightButton,
            &_middleButton, &_firstExtraButton,
            &_secondExtraButton
        };

    private:
        friend class Render::WindowsManager::BindsEngine::InputSystem;

    public:
        Core::Vector2 GetMousePos();
        Core::Vector2 GetMouseDelta();

        [[nodiscard]] bool IsMouseChangePosition() const;

        ~Mouse() = default;

    private:
        Mouse() = default;

        void UpdateMouseState();
    };
}
