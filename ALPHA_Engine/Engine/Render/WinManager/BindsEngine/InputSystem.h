#pragma once
#include <list>
#include <memory>

namespace Render::WindowsManager::BindsEngine {
    class Mouse;
    class Keyboard;
    class Bind;
}

namespace Core {
    class World;
};

struct GLFWwindow;

namespace Render::WindowsManager::BindsEngine {

class InputSystem {
    friend class Core::World;

private:
    std::list<Bind> _bindsBuff;

    std::unique_ptr<Mouse> _mouseClass;
    std::unique_ptr<Keyboard> _keyboardClass;

private:
    static InputSystem* GetInstance();
    InputSystem() = default;
    void IO_Events(GLFWwindow& window);

public:
    void ClearBindsBuffer();
    void InsertBind(const Bind& bind);

    ~InputSystem() = default;
};

}