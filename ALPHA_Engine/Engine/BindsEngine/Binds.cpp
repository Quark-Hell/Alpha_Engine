#include "Binds.h"

namespace BindsEngine {
    void Bind::Create(
        const std::vector<std::function<void(void)> > &Operations,
        const std::vector<EnumKeyboardKeysStates> &KeyboardKeysState,
        const std::vector<EnumKeyboardTable> &KeyboardKeys,
        const std::vector<EnumMouseKeysStates> &MouseKeysState,
        const std::vector<EnumMouseTable> &MouseKeys,
        const std::vector<EnumMouseSensorStates>& MouseSensorState,
        WindowsManager::Window *window) {
        _operations = Operations;

        _keyboardKeysState = KeyboardKeysState;
        _keyboardKeys = KeyboardKeys;

        _mouseKeysState = MouseKeysState;
        _mouseKeys = MouseKeys;

        _mouseSensorState = MouseSensorState;

        _bindedWindow = window;
    }

    void Bind::InvokeOperations(const WindowsManager::Window *window) const {
        if (_bindedWindow != nullptr && _bindedWindow != window) {
            return;
        }
        if (IsActive == false) {
            return;
        }

        for (const auto &_operation: Bind::_operations) {
            _operation();
        }
    }
}
