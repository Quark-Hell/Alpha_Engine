#pragma once
#include "Binds.h"
#include "Core/ECS/TSystemData.h"

namespace BindsEngine {
    class BindsBuffer final : public Core::TSystemData<Bind> {
        friend class InputSystem;

    public:
        BindsBuffer();
        Bind *CreateGeneralBind();

        Bind *CreateMouseButtonsBind(
            const std::vector<std::function<void()>> &Operations,
            const std::vector<EnumMouseKeysStates> &MouseKeysState,
            const std::vector<EnumMouseTable> &MouseKeys,
            Render::WindowsManager::Window *window);

        Bind *CreateMouseSensorBind(
            const std::vector<std::function<void()>> &Operations,
            const std::vector<EnumMouseSensorStates>& MouseSensorState,
            Render::WindowsManager::Window *window);

        Bind *CreateKeyboardBind(
            const std::vector<std::function<void()>> &Operations,
            const std::vector<EnumKeyboardKeysStates> &KeysState,
            const std::vector<EnumKeyboardTable> &KeyboardKeys,
            Render::WindowsManager::Window *window);

        ~BindsBuffer() override = default;
    };
}
