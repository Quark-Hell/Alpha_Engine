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

namespace Render::WindowsManager::BindsEngine {
    class InputSystem {
        friend class Render::WindowsManager::WindowsManager;

    private:
        std::list<std::unique_ptr<Bind>>* _bindsBuffer = nullptr;
        std::unique_ptr<Mouse> _mouseClass;
        std::unique_ptr<Keyboard> _keyboardClass;

    private:
        InputSystem();
        void IO_Events(const Render::WindowsManager::Window *window) const;

    public:
        static InputSystem *GetInstance();

        void LoadBindsBuffer(std::list<std::unique_ptr<Bind> > *buffer);

        ~InputSystem() = default;

        Mouse *GetMouse() const;
        Keyboard *GetKeyboard() const;
    };
}
