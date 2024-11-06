#include "Binds.h"

#include <GLFW/glfw3.h>
#include <Render/WinManager/Window.h>

namespace Render::WindowsManager::BindsEngine {

void Bind::Create(
	const std::vector<std::function<void(void)>> &Operations,
	const std::vector<EnumKeyStates> &KeysState,
	const std::vector<EnumKeyboardTable> &KeyboardKeys,
	const std::vector<EnumKeyStates> &MouseKeysState,
	const std::vector<uint8_t> &MouseKeys,
	const EnumMouseSensorStates MouseSensorState,
	Window* window) {

	_operations = Operations;

	_keyboardKeysState = KeysState;
	_keyboardKeys = KeyboardKeys;

	_mouseKeysState = MouseKeysState;
	_mouseKeys = MouseKeys;

	_mouseSensorState = MouseSensorState;

	_bindedWindow = window;
}

void Bind::InvokeOperations(const Render::WindowsManager::Window* window) const {
	if (_bindedWindow != nullptr && _bindedWindow == window) {
		return;
	}

	for (const auto & _operation : Bind::_operations)
	{
		_operation();
	}
}

}
