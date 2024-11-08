#pragma once
#include "MouseSensors.h"
#include "Core/Math/Vectors.h"

struct GLFWwindow;

namespace Render::WindowsManager::BindsEngine {

    class Mouse {
        friend class InputSystem;

    private:
        Mouse() = default;
        void UpdateMouseState();

    public:
        Core::Vector2 GetMousePos();
        Core::Vector2 GetMouseDelta();

        [[nodiscard]] bool IsMouseChangePosition() const;

        EnumMouseKeysStates GetKeyState(EnumMouseTable key);
        EnumMouseSensorStates GetSensorState();

        ~Mouse() = default;
    };
}
