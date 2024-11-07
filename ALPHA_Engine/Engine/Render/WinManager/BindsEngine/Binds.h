#pragma once

#include <BaseConfig.h>
#include <Render/WinManager/BindsEngine/Mouse/Mouse.h>
#include <Render/WinManager/BindsEngine/GeneralSensors.h>
#include <functional>

namespace Render::WindowsManager {
    class Window;
}

namespace Core {
    class Factory;
}

namespace Render::WindowsManager::BindsEngine {
    enum class EnumKeyboardTable : uint16_t;

    class Bind {
    private:
        std::vector<std::function<void(void)> > _operations;

        std::vector<EnumKeyStates> _keyboardKeysState;
        std::vector<EnumKeyboardTable> _keyboardKeys;
        std::vector<EnumKeyStates> _mouseKeysState;
        std::vector<uint8_t> _mouseKeys;
        EnumMouseSensorStates _mouseSensorState;

        Window *_bindedWindow = nullptr;

    public:
        bool IsActive = true;

    private:
        friend class InputSystem;
        friend class Core::Factory;

    private:
        Bind() = default;

        void InvokeOperations(const Render::WindowsManager::Window *window) const;

        void Create(const std::vector<std::function<void(void)> > &Operations = {},
                    const std::vector<EnumKeyStates> &KeysState = {},
                    const std::vector<EnumKeyboardTable> &KeyboardKeys = {},
                    const std::vector<EnumKeyStates> &MouseKeysState = {},
                    const std::vector<uint8_t> &MouseKeys = {},
                    EnumMouseSensorStates MouseSensorState = static_cast<EnumMouseSensorStates>(1),
                    Window *window = nullptr);

    public:
        ~Bind() = default;
    };
}
