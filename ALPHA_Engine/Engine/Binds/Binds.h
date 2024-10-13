#pragma once

#include "BaseConfig.h"
#include "GLFW/glfw3.h"
#include "Mouse/Mouse.h"
#include "GeneralSensors.h"

namespace BindsEngine {

class Bind {
private:
	std::vector<void(*)()> _operations;

	std::vector<EnumKeyStates> _keyboardKeysState;
	std::vector<uint16_t> _keyboardKeys;
	std::vector<EnumKeyStates> _mouseKeysState;
	std::vector<uint8_t> _mouseKeys;
	EnumMouseSensorStates _mouseSensorState{};

public:
	bool Active = true;

private:
	friend class InputSystem;

private:
	void InvokeOperations();
	void Constructor(std::vector<void(*)()> Operations = {},
		std::vector<EnumKeyStates> KeysState = {},
		std::vector<uint16_t> KeyboardKeys = {},
		std::vector<EnumKeyStates> MouseKeysState = {},
		std::vector<uint8_t> MouseKeys = {},
		EnumMouseSensorStates MouseSensorState = (EnumMouseSensorStates)(1));

#pragma region Constructor for mouse buttons bind
public:
	void MouseButtonsBind(
		std::vector<void(*)()> Operations,
		std::vector<EnumKeyStates> MouseKeysState,
		std::vector<uint8_t> MouseKeys);
#pragma endregion

#pragma region Constructor for mouse sensor bind
public:
	void MouseSensorBind(
		std::vector<void(*)()> Operations,
		EnumMouseSensorStates MouseSensorState);
#pragma endregion
};

}