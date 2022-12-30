#include "IO.h"

inline Bind::Bind(std::vector<void(*)()> Operations,
	std::vector<EnumKeyStates> KeysState,
	std::vector<sf::Keyboard::Key> KeyboardKeys,
	sf::Mouse::Button MouseKey) {

	Bind::Operations = Operations;
	Bind::KeysState = KeysState;
	Bind::KeyboardKeys = KeyboardKeys;
	Bind::MouseKey = MouseKey;
}

inline void Bind::InvokeOperations() {
	for (size_t i = 0; i < Bind::Operations.size(); i++)
	{
		Bind::Operations[i]();
	}
}

inline void InputSystem::IO_Events() {
	InputSystem::MouseClass->UpdateMouseInfo();
	InputSystem::KeyboardClass->UpdateKeysState();

	if (InputSystem::ScreenClass->_screen->pollEvent(InputSystem::Event)) {}

	//All values
	for (size_t i = 0; i < InputSystem::BindsBuff.size(); i++)
	{
		bool mark = true;
		//Current values
		for (size_t j = 0; j < InputSystem::BindsBuff[i].KeyboardKeys.size(); j++)
		{
			int IdCurrentKey = InputSystem::BindsBuff[i].KeyboardKeys[j];
			if (! (InputSystem::BindsBuff[i].KeysState[j] == InputSystem::KeyboardClass->Keys[IdCurrentKey]->KeyState)) { mark = false; break; }
		}
		if (mark) { InputSystem::BindsBuff[i].InvokeOperations(); }
	}
}

inline void InputSystem::ClearBindsBuffer() {
	InputSystem::BindsBuff.clear();
}
inline void InputSystem::InsertBindWithClear(Bind bind) {
	ClearBindsBuffer();
	InputSystem::BindsBuff.push_back(bind);
}
inline void InputSystem::InsertBind(Bind bind) {
	InputSystem::BindsBuff.push_back(bind);
}

inline void Keyboard::UpdateKeysState() {
	for (size_t i = 0; i < 103; i++)
	{		
		if (sf::Keyboard::isKeyPressed(Keys[i]->Key)) {
			if (Keys[i]->KeyState & EnumKeyStates::KeyNotPressed) {
				Keys[i]->KeyState = (EnumKeyStates)(KeyPressed | KeyHold);
				continue;
			}
			else if (Keys[i]->KeyState & EnumKeyStates::KeyPressed) {
				Keys[i]->KeyState = KeyHold;
				continue;
			}
		}
		else
		{
			if (Keys[i]->KeyState & EnumKeyStates::KeyHold || Keys[i]->KeyState & EnumKeyStates::KeyPressed || Keys[i]->KeyState & (EnumKeyStates)(KeyPressed | KeyHold)) {
				Keys[i]->KeyState = KeyReleased;
				continue;
			}
			Keys[i]->KeyState = KeyNotPressed;
			continue;
		}
	}
}

inline Mouse* InputSystem::GetMouseClass() {
	return InputSystem::MouseClass;
}

inline void Mouse::UpdateMouseInfo() {
	Mouse::_previousMousePos = Mouse::_currentMousePos;
	Mouse::_currentMousePos = { (float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y };

	Mouse::_mouseDelta = Vector3{ _currentMousePos - _previousMousePos };
}

inline Vector3 Mouse::GetMouseDelta() {
	return _mouseDelta;
}
inline Vector3 Mouse::GetMousePos() {
	return _currentMousePos;
}
inline bool Mouse::IsMouseChangePosition() {
	if (Mouse::_mouseDelta == Vector3{ 0,0,0 }) {
		return false;
	}
	return true;
}