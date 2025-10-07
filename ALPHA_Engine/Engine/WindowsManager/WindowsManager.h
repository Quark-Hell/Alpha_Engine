#pragma once
#include "Core/ECS/System.h"

namespace WindowsManager {
    class WindowsManager final : public Core::System {
    private:
        void EntryPoint(std::vector<Core::SystemData*>& data) override;

    public:
        WindowsManager(size_t order);
        ~WindowsManager() override = default;
    };
}
