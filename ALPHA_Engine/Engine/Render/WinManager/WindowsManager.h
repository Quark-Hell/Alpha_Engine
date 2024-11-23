#pragma once
#include "Core/ECS/System.h"

namespace Render::WindowsManager {
    class WindowsManager final : public Core::System {

    private:
        void EntryPoint(std::vector<Core::SystemData*>& data) override;

    public:
        WindowsManager();
        ~WindowsManager() override = default;
    };
}
