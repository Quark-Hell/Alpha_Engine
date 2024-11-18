#pragma once

#include <BaseConfig.h>
#include <functional>

namespace Render::WindowsManager {
    class Window;
}

namespace Core {
    class Factory;
}

namespace Render::WindowsManager::BindsEngine {
    enum class EnumMouseKeysStates : uint8_t;
    enum class EnumKeyboardKeysStates : uint8_t;
    enum class EnumKeyboardTable : uint16_t;

    enum class EnumMouseSensorStates : uint8_t;
    enum class EnumMouseTable : uint8_t;

    class Bind {
    private:
        std::vector<std::function<void(void)> > _operations;

        std::vector<EnumKeyboardKeysStates> _keyboardKeysState;
        std::vector<EnumKeyboardTable> _keyboardKeys;
        std::vector<EnumMouseKeysStates> _mouseKeysState;
        std::vector<EnumMouseTable> _mouseKeys;
        std::vector<EnumMouseSensorStates> _mouseSensorState;

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
                    const std::vector<EnumKeyboardKeysStates> &KeyboardKeysState = {},
                    const std::vector<EnumKeyboardTable> &KeyboardKeys = {},
                    const std::vector<EnumMouseKeysStates> &MouseKeysState = {},
                    const std::vector<EnumMouseTable> &MouseKeys = {},
                    const std::vector<EnumMouseSensorStates>& MouseSensorState = {},
                    Window *window = nullptr);

    public:
        ~Bind() = default;
    };
}
