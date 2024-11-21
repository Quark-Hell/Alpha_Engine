#pragma once
#include <memory>

#include "Core/ECS/System.h"

namespace Render::WindowsManager::BindsEngine {
    class Mouse;
    class Keyboard;
    class Bind;
}

namespace Render::WindowsManager::BindsEngine {
    class InputSystem final : Core::System {
    private:
        std::unique_ptr<Mouse> _mouseClass;
        std::unique_ptr<Keyboard> _keyboardClass;

    private:
        InputSystem();
        void EntryPoint(std::vector<Core::SystemData*>& data) override;

    public:
        static InputSystem *GetInstance();

        ~InputSystem() override = default;

        [[nodiscard]] Mouse *GetMouse() const;
        [[nodiscard]] Keyboard *GetKeyboard() const;
    };

    inline InputSystem* inputSystem = InputSystem::GetInstance();
}
