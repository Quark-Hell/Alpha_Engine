#pragma once
#include "KeyboardSensors.h"

class GLFWwindow;

namespace BindsEngine {

class Keyboard {
private:
    friend class InputSystem;

private:
    EnumKeyStates GetKeyState(uint16_t key);
    void UpdateKeysState(GLFWwindow& window);

public:
    Keyboard();
    ~Keyboard();
};

}