#pragma once
#include "Core/ECS/System.h"

struct GLFWwindow;

namespace BindsEngine {
    class KeyboardSystem final : public Core::System {
    private:
        void EntryPoint(std::vector<Core::SystemData*>& data) override;

    public:
        KeyboardSystem(size_t order);
        ~KeyboardSystem() override = default;
    };
}
