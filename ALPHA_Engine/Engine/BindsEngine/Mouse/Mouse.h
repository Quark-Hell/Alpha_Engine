#pragma once
#include "Core/ECS/System.h"

struct GLFWwindow;

namespace BindsEngine {
    class MouseSystem final : public Core::System {
        void EntryPoint(std::vector<Core::SystemData*>& data) override;

    public:
        MouseSystem();
        ~MouseSystem() override = default;
    };
}
