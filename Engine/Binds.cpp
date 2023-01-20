#include "Binds.h"

inline Bind::Bind(std::vector<void(*)()> Operations,
	sf::Event::EventType EventType,
	std::vector<EnumKeyStates> KeysState,
	std::vector<sf::Keyboard::Key> KeyboardKeys,
	std::vector<EnumKeyStates> MouseKeysState,
	std::vector<sf::Mouse::Button> MouseKeys,
	EnumMouseSensorStates MouseSensorState) {

	Bind::Operations = Operations;
	Bind::EventType = EventType;

	Bind::KeyboardKeysState = KeysState;
	Bind::KeyboardKeys = KeyboardKeys;

	Bind::MouseKeysState = MouseKeysState;
	Bind::MouseKeys = MouseKeys;

	Bind::MouseSensorState = MouseSensorState;
}

inline void Bind::InvokeOperations() {
	for (size_t i = 0; i < Bind::Operations.size(); i++)
	{
		Bind::Operations[i]();
	}
}

inline void InputSystem::IO_Events() {
	InputSystem::MouseClass->UpdateMouseState();
	InputSystem::KeyboardClass->UpdateKeysState();

	if (!InputSystem::ScreenClass->_screen->isOpen()) { return; }
	if (InputSystem::ScreenClass->_screen->pollEvent(InputSystem::Event)) { }


	//All values
	for (size_t i = 0; i < InputSystem::BindsBuff.size(); i++)
	{
		bool mark = true;

		//Check event type statement
		if (InputSystem::BindsBuff[i].EventType == (sf::Event::EventType)- 1) {}
		else if (!(InputSystem::BindsBuff[i].EventType == Event.type)) { mark = false; }

		//Keyboard statement check
		for (size_t j = 0; j < InputSystem::BindsBuff[i].KeyboardKeys.size(); j++)
		{
			int IdCurrentKey = InputSystem::BindsBuff[i].KeyboardKeys[j];
			if (! (InputSystem::BindsBuff[i].KeyboardKeysState[j] == InputSystem::KeyboardClass->Keys[IdCurrentKey]->KeyState)) { mark = false; break; }
		}

		//Mouse button statement check
		for (size_t j = 0; j < InputSystem::BindsBuff[i].MouseKeys.size(); j++)
		{
			int IdCurrentKey = InputSystem::BindsBuff[i].MouseKeys[j];
			if (!(InputSystem::BindsBuff[i].MouseKeysState[j] == InputSystem::MouseClass->Buttons[IdCurrentKey]->KeyState)) { mark = false; break; }
		}		

		//Check mouse sensor statement
		if(InputSystem::BindsBuff[i].MouseSensorState & UnknownState) {}
		else if (!(InputSystem::BindsBuff[i].MouseSensorState == InputSystem::MouseClass->MoveSensorState)) { mark = false; }

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
	for (size_t i = 0; i < 101; i++)
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

inline void Mouse::UpdateMouseState() {
	Mouse::_previousMousePos = Mouse::_currentMousePos;
	Mouse::_currentMousePos = { (float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y };

	Mouse::_mouseDelta = Vector3{ _currentMousePos - _previousMousePos };

	if (Mouse::_mouseDelta != Vector3{0,0,0}) {
		if (Mouse::MoveSensorState & MouseNotMoved || Mouse::MoveSensorState & MouseEndMoved) {
			Mouse::MoveSensorState = EnumMouseSensorStates(MouseStartMoved | MouseKeepMoved);
		}
		else if (Mouse::MoveSensorState & (MouseStartMoved | MouseKeepMoved)) {
			Mouse::MoveSensorState = MouseKeepMoved;
		}
	}
	else
	{
		if (Mouse::MoveSensorState & MouseKeepMoved || Mouse::MoveSensorState & (MouseStartMoved | MouseKeepMoved)) {
			Mouse::MoveSensorState = MouseEndMoved;
		}
		else
		{
			Mouse::MoveSensorState = MouseNotMoved;
		}
	}

	//Update mouse buttons state
	for (size_t i = 0; i < 5; i++)
	{
		if (sf::Mouse::isButtonPressed(Buttons[i]->Key)) {
			if (Buttons[i]->KeyState & EnumKeyStates::KeyNotPressed) {
				Buttons[i]->KeyState = (EnumKeyStates)(KeyPressed | KeyHold);
				continue;
			}
			else if (Buttons[i]->KeyState & EnumKeyStates::KeyPressed) {
				Buttons[i]->KeyState = KeyHold;
				continue;
			}
		}
		else
		{
			if (Buttons[i]->KeyState & EnumKeyStates::KeyHold || Buttons[i]->KeyState & EnumKeyStates::KeyPressed || Buttons[i]->KeyState & (EnumKeyStates)(KeyPressed | KeyHold)) {
				Buttons[i]->KeyState = KeyReleased;
				continue;
			}
			Buttons[i]->KeyState = KeyNotPressed;
			continue;
		}
	}
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