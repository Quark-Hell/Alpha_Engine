#pragma once

#include <cstdint>
#include <functional>

namespace Render::WindowsManager {
    class Window;
}

namespace BindsEngine {
    enum class EnumMouseKeysStates : uint8_t;
    enum class EnumKeyboardKeysStates : uint8_t;
    enum class EnumKeyboardTable : uint16_t;

    enum class EnumMouseSensorStates : uint8_t;
    enum class EnumMouseTable : uint8_t;

    class Bind {
        friend class BindsBuffer;
        friend class InputSystem;

    private:
        std::vector<std::function<void(void)> > _operations;

        std::vector<EnumKeyboardKeysStates> _keyboardKeysState;
        std::vector<EnumKeyboardTable> _keyboardKeys;
        std::vector<EnumMouseKeysStates> _mouseKeysState;
        std::vector<EnumMouseTable> _mouseKeys;
        std::vector<EnumMouseSensorStates> _mouseSensorState;

        Render::WindowsManager::Window *_bindedWindow = nullptr;

    public:
        bool IsActive = true;

    private:
        Bind() = default;

        void InvokeOperations(const Render::WindowsManager::Window *window) const;

        void Create(const std::vector<std::function<void(void)> > &Operations = {},
                    const std::vector<EnumKeyboardKeysStates> &KeyboardKeysState = {},
                    const std::vector<EnumKeyboardTable> &KeyboardKeys = {},
                    const std::vector<EnumMouseKeysStates> &MouseKeysState = {},
                    const std::vector<EnumMouseTable> &MouseKeys = {},
                    const std::vector<EnumMouseSensorStates>& MouseSensorState = {},
                    Render::WindowsManager::Window *window = nullptr);

    public:
        ~Bind() = default;
    };
}
