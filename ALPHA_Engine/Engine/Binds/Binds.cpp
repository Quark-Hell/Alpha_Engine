#include "Binds.h"

#include "Mouse/MousePos.h"

namespace BindsEngine {

void Bind::Constructor(std::vector<void(*)()> Operations,
	std::vector<EnumKeyStates> KeysState,
	std::vector<uint16_t> KeyboardKeys,
	std::vector<EnumKeyStates> MouseKeysState,
	std::vector<uint8_t> MouseKeys,
	EnumMouseSensorStates MouseSensorState) {

	Bind::_operations = Operations;

	Bind::_keyboardKeysState = KeysState;
	Bind::_keyboardKeys = KeyboardKeys;

	Bind::_mouseKeysState = MouseKeysState;
	Bind::_mouseKeys = MouseKeys;

	Bind::_mouseSensorState = MouseSensorState;
}

void Bind::GeneralBind(std::vector<void(*)()> Operations,
	std::vector<EnumKeyStates> KeysState,
	std::vector<uint16_t> KeyboardKeys,
	std::vector<EnumKeyStates> MouseKeysState,
	std::vector<uint8_t> MouseKeys,
	EnumMouseSensorStates MouseSensorState) {

	Bind::Constructor(Operations, KeysState, KeyboardKeys, MouseKeysState, MouseKeys, MouseSensorState);
}

void BindsEngine::Bind::KeyboardBind(std::vector<void(*)()> Operations,
	std::vector<EnumKeyStates> KeysState,
	std::vector<uint16_t> KeyboardKeys) {

	Bind::Constructor(Operations, KeysState, KeyboardKeys, {}, {}, (EnumMouseSensorStates)(1));
}

void Bind::MouseButtonsBind(std::vector<void(*)()> Operations,
	std::vector<EnumKeyStates> MouseKeysState,
	std::vector<uint8_t> MouseKeys) {

	Bind::Constructor(Operations, {}, {}, MouseKeysState, MouseKeys, (EnumMouseSensorStates)(1));
}

void Bind::MouseSensorBind(std::vector<void(*)()> Operations,
	EnumMouseSensorStates MouseSensorState) {

	Bind::Constructor(Operations, {}, {}, {}, {}, MouseSensorState);
}

void Bind::InvokeOperations() {
	for (size_t i = 0; i < Bind::_operations.size(); i++)
	{
		Bind::_operations[i]();
	}
}

}
