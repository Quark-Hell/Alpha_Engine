#pragma once
#include <vector>

namespace BindsEngine {

class InputSystem {
private:
    std::vector<Bind> _bindsBuff;

    Mouse* _mouseClass = new Mouse;
    Keyboard* _keyboardClass = new Keyboard;

public:
    GLFWwindow* Window;

public:
    void IO_Events();

    void ClearBindsBuffer();
    void InsertBindWithClear(Bind bind);
    void InsertBind(Bind bind);

    Mouse* GetMouseClass();

    InputSystem();
    ~InputSystem();
};

}