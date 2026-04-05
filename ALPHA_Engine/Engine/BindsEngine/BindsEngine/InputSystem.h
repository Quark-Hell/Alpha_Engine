#pragma once
#include "Core/ECS/System.h"

namespace BindsEngine {
    class MouseSystem;
    class KeyboardSystem;
    class Bind;
}

namespace BindsEngine {
    class InputSystem final : Core::System {
    private:
        void EntryPoint(std::vector<Core::SystemData*>& data) override;

    public:
        InputSystem();
        ~InputSystem() override = default;
    };
}
