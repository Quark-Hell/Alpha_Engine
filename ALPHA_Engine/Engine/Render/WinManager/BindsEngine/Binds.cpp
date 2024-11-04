#include "Binds.h"

namespace Render::WindowsManager::BindsEngine {

void Bind::Constructor(const std::vector<void(*)()> &Operations,
	const std::vector<EnumKeyStates> &KeysState,
	const std::vector<uint16_t> &KeyboardKeys,
	const std::vector<EnumKeyStates> &MouseKeysState,
	const std::vector<uint8_t> &MouseKeys,
	const EnumMouseSensorStates MouseSensorState) {

	_operations = Operations;

	_keyboardKeysState = KeysState;
	_keyboardKeys = KeyboardKeys;

	_mouseKeysState = MouseKeysState;
	_mouseKeys = MouseKeys;

	_mouseSensorState = MouseSensorState;
}

void Bind::KeyboardBind(const std::vector<void(*)()>& Operations,
	const std::vector<EnumKeyStates>& KeysState,
	const std::vector<uint16_t>& KeyboardKeys) {

	Bind::Constructor(Operations, KeysState, KeyboardKeys, {}, {}, static_cast<EnumMouseSensorStates>(1));
}

void Bind::MouseButtonsBind(const std::vector<void(*)()>& Operations,
	const std::vector<EnumKeyStates>& MouseKeysState,
	const std::vector<uint8_t>& MouseKeys) {

	Bind::Constructor(Operations, {}, {}, MouseKeysState, MouseKeys, static_cast<EnumMouseSensorStates>(1));
}

void Bind::MouseSensorBind(const std::vector<void(*)()>& Operations,
	const EnumMouseSensorStates MouseSensorState) {

	Bind::Constructor(Operations, {}, {}, {}, {}, MouseSensorState);
}

void Bind::InvokeOperations() const {
	for (const auto & _operation : Bind::_operations)
	{
		_operation();
	}
}

}
