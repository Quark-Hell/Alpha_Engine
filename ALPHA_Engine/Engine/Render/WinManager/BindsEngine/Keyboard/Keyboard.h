#pragma once
#include "KeyboardSensors.h"

struct GLFWwindow;

namespace Render::WindowsManager::BindsEngine {
    class Keyboard {
        friend class InputSystem;

    private:
        Keyboard() = default;
        void UpdateKeysState();

    public:
        ~Keyboard() = default;
        EnumKeyboardKeysStates GetKeyState(EnumKeyboardTable key);
    };
}
