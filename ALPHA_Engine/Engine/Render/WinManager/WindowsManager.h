#pragma once
#include "Core/ECS/System.h"

namespace Render::WindowsManager {
    class WindowsManager final : public Core::System {

    private:
        WindowsManager();

        void EntryPoint(Core::SystemData& data) override;

    public:
        ~WindowsManager() override = default;

        static WindowsManager *GetInstance();
    };

    //Registration system in World
    inline Render::WindowsManager::WindowsManager* WindowsSystem = Render::WindowsManager:: WindowsManager::GetInstance();
}
