#pragma once
#include "KeyboardSensors.h"

struct GLFWwindow;

namespace Render::WindowsManager::BindsEngine {

class Keyboard {
private:
    friend class InputSystem;

private:
    Keyboard();

    EnumKeyStates GetKeyState(uint16_t key);
    void UpdateKeysState();

public:
    ~Keyboard();
};

}