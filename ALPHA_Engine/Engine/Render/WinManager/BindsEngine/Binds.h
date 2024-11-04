#pragma once

#include "BaseConfig.h"
#include "GLFW/glfw3.h"
#include "Mouse/Mouse.h"
#include "GeneralSensors.h"

namespace Render::WindowsManager::BindsEngine {

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
	void InvokeOperations() const;
	void Constructor(const std::vector<void(*)()> &Operations = {},
		const std::vector<EnumKeyStates> &KeysState = {},
		const std::vector<uint16_t> &KeyboardKeys = {},
		const std::vector<EnumKeyStates> &MouseKeysState = {},
		const std::vector<uint8_t> &MouseKeys = {},
		EnumMouseSensorStates MouseSensorState = static_cast<EnumMouseSensorStates>(1));


#pragma region Constructor for keyboard bind
public:
	void KeyboardBind(
		const std::vector<void(*)()>& Operations,
		const std::vector<EnumKeyStates>& KeysState,
		const std::vector<uint16_t>& KeyboardKeys);
#pragma endregion

#pragma region Constructor for mouse buttons bind
public:
	void MouseButtonsBind(
		const std::vector<void(*)()>& Operations,
		const std::vector<EnumKeyStates>& MouseKeysState,
		const std::vector<uint8_t>& MouseKeys);
#pragma endregion

#pragma region Constructor for mouse sensor bind
public:
	void MouseSensorBind(
		const std::vector<void(*)()>& Operations,
		EnumMouseSensorStates MouseSensorState);
#pragma endregion
};

}