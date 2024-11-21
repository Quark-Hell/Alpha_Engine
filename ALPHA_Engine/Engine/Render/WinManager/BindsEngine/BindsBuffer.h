#pragma once
#include "Binds.h"
#include "Core/ECS/TSystemData.h"

namespace Render::WindowsManager::BindsEngine {
    class BindsBuffer final : public Core::TSystemData<Bind>{
        friend class InputSystem;

    private:
        BindsBuffer();

    public:
        static BindsBuffer *GetInstance();

        static Bind *CreateGeneralBind();

        static Bind *CreateMouseButtonsBind(
            const std::vector<std::function<void()>> &Operations,
            const std::vector<EnumMouseKeysStates> &MouseKeysState,
            const std::vector<EnumMouseTable> &MouseKeys,
            Window *window);

        static Bind *CreateMouseSensorBind(
            const std::vector<std::function<void()>> &Operations,
            const std::vector<EnumMouseSensorStates>& MouseSensorState,
            Window *window);

        static Bind *CreateKeyboardBind(
            const std::vector<std::function<void()>> &Operations,
            const std::vector<EnumKeyboardKeysStates> &KeysState,
            const std::vector<EnumKeyboardTable> &KeyboardKeys,
            Window *window);

        ~BindsBuffer() override = default;
    };

    inline BindsBuffer* bindsBuffer = BindsBuffer::GetInstance();
}
