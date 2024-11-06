#pragma once
#include <list>
#include <memory>

namespace Render::WindowsManager {
    class Window;
    class WindowsManager;
}

namespace Render::WindowsManager::BindsEngine {
    class Mouse;
    class Keyboard;
    class Bind;
}

namespace Core {
    class Host;
};

namespace Render::WindowsManager::BindsEngine {

class InputSystem {
    friend class Core::Host;
    friend class Render::WindowsManager::WindowsManager;

private:
    std::list<std::unique_ptr<Render::WindowsManager::BindsEngine::Bind>>* bindsBuffer = nullptr;
    std::unique_ptr<Mouse> _mouseClass;
    std::unique_ptr<Keyboard> _keyboardClass;

private:
    static InputSystem* GetInstance();
    InputSystem();
    void IO_Events(const Render::WindowsManager::Window* window) const;


public:
    void LoadBindsBuffer(std::list<std::unique_ptr<Render::WindowsManager::BindsEngine::Bind>>* buffer);
    ~InputSystem() = default;
};

}