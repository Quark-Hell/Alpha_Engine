#include "Binds.h"

//----------------------------------------------------------------------------//
#pragma region Bind definitions

inline void Bind::Constructor(std::vector<void(*)()> Operations,
	std::vector<EnumKeyStates> KeysState,
	std::vector<sf::Keyboard::Key> KeyboardKeys,
	std::vector<EnumKeyStates> MouseKeysState,
	std::vector<sf::Mouse::Button> MouseKeys,
	EnumMouseSensorStates MouseSensorState,
	sf::Event::EventType EventType) {

	Bind::_operations = Operations;
	Bind::_eventType = EventType;

	Bind::_keyboardKeysState = KeysState;
	Bind::_keyboardKeys = KeyboardKeys;

	Bind::_mouseKeysState = MouseKeysState;
	Bind::_mouseKeys = MouseKeys;

	Bind::_mouseSensorState = MouseSensorState;
}

//---------------------------------------------------------------//
#pragma region General constructor
inline void Bind::GeneralBind(std::vector<void(*)()> Operations,
	std::vector<EnumKeyStates> KeysState,
	std::vector<sf::Keyboard::Key> KeyboardKeys,
	std::vector<EnumKeyStates> MouseKeysState,
	std::vector<sf::Mouse::Button> MouseKeys,
	EnumMouseSensorStates MouseSensorState,
	sf::Event::EventType EventType) {

	Bind::Constructor(Operations, KeysState, KeyboardKeys, MouseKeysState, MouseKeys, MouseSensorState, EventType);
}
#pragma endregion
//---------------------------------------------------------------//



//---------------------------------------------------------------//
#pragma region Constructor for keyboard bind
inline void Bind::KeyboardBind(std::vector<void(*)()> Operations,
	std::vector<EnumKeyStates> KeysState,
	std::vector<sf::Keyboard::Key> KeyboardKeys,
	sf::Event::EventType EventType) {

	Bind::Constructor(Operations, KeysState, KeyboardKeys, {}, {}, (EnumMouseSensorStates)(1), EventType);
}

inline void Bind::KeyboardBind(std::vector<void(*)()> Operations,
	std::vector<EnumKeyStates> KeysState,
	std::vector<sf::Keyboard::Key> KeyboardKeys) {

	Bind::Constructor(Operations, KeysState, KeyboardKeys, {}, {}, (EnumMouseSensorStates)(1), (sf::Event::EventType)-1);
}
#pragma endregion
//---------------------------------------------------------------//


//---------------------------------------------------------------//
#pragma region Constructor for mouse buttons bind
inline void Bind::MouseButtonsBind(std::vector<void(*)()> Operations,
	std::vector<EnumKeyStates> MouseKeysState,
	std::vector<sf::Mouse::Button> MouseKeys,
	sf::Event::EventType EventType) {

	Bind::Constructor(Operations, {}, {}, MouseKeysState, MouseKeys, (EnumMouseSensorStates)(1), EventType);
}

inline void Bind::MouseButtonsBind(std::vector<void(*)()> Operations,
	std::vector<EnumKeyStates> MouseKeysState,
	std::vector<sf::Mouse::Button> MouseKeys) {

	Bind::Constructor(Operations, {}, {}, MouseKeysState, MouseKeys, (EnumMouseSensorStates)(1), (sf::Event::EventType)-1);
}
#pragma endregion
//---------------------------------------------------------------//


//---------------------------------------------------------------//
#pragma region Constructor for mouse sensor bind
inline void Bind::MouseSensorBind(std::vector<void(*)()> Operations,
	EnumMouseSensorStates MouseSensorState,
	sf::Event::EventType EventType) {

	Bind::Constructor(Operations, {}, {}, {}, {}, MouseSensorState, EventType);
}

inline void Bind::MouseSensorBind(std::vector<void(*)()> Operations,
	EnumMouseSensorStates MouseSensorState) {

	Bind::Constructor(Operations, {}, {}, {}, {}, MouseSensorState, (sf::Event::EventType)-1);
}
#pragma endregion
//---------------------------------------------------------------//

inline void Bind::InvokeOperations() {
	for (size_t i = 0; i < Bind::_operations.size(); i++)
	{
		Bind::_operations[i]();
	}
}
#pragma endregion
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
#pragma region InputSystem definitions
inline void InputSystem::IO_Events() {
	if (!InputSystem::Screen) { return; }

	InputSystem::_mouseClass->UpdateMouseState();
	InputSystem::_keyboardClass->UpdateKeysState();

	if (!InputSystem::Screen->isOpen()) { return; }
	if (InputSystem::Screen->pollEvent(InputSystem::_event)) { }


	//All values
	for (size_t i = 0; i < InputSystem::_bindsBuff.size(); i++)
	{
		bool mark = true;

		//Check event type statement
		if (InputSystem::_bindsBuff[i]._eventType == (sf::Event::EventType)- 1) {}
		else if (!(InputSystem::_bindsBuff[i]._eventType == _event.type)) { mark = false; }

		//Keyboard statement check
		for (size_t j = 0; j < InputSystem::_bindsBuff[i]._keyboardKeys.size(); j++)
		{
			int IdCurrentKey = InputSystem::_bindsBuff[i]._keyboardKeys[j];
			if (! (InputSystem::_bindsBuff[i]._keyboardKeysState[j] == InputSystem::_keyboardClass->Keys[IdCurrentKey]->KeyState)) { mark = false; break; }
		}

		//Mouse button statement check
		for (size_t j = 0; j < InputSystem::_bindsBuff[i]._mouseKeys.size(); j++)
		{
			int IdCurrentKey = InputSystem::_bindsBuff[i]._mouseKeys[j];
			if (!(InputSystem::_bindsBuff[i]._mouseKeysState[j] == InputSystem::_mouseClass->Buttons[IdCurrentKey]->KeyState)) { mark = false; break; }
		}		

		//Check mouse sensor statement
		if(InputSystem::_bindsBuff[i]._mouseSensorState & UnknownState) {}
		else if (!(InputSystem::_bindsBuff[i]._mouseSensorState == InputSystem::_mouseClass->MoveSensorState)) { mark = false; }

		if (mark) { InputSystem::_bindsBuff[i].InvokeOperations(); }
	}
}

inline void InputSystem::ClearBindsBuffer() {
	InputSystem::_bindsBuff.clear();
}
inline void InputSystem::InsertBindWithClear(Bind bind) {
	ClearBindsBuffer();
	InputSystem::_bindsBuff.push_back(bind);
}
inline void InputSystem::InsertBind(Bind bind) {
	InputSystem::_bindsBuff.push_back(bind);
	printf("I'm work");
}

inline InputSystem::InputSystem() {
	InputSystem::Screen = Screen;
}
inline InputSystem::~InputSystem() {

}
#pragma endregion
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
#pragma region Keyboard definitions
inline void Keyboard::UpdateKeysState() {
	for (size_t i = 0; i < 101; i++)
	{		
		if (sf::Keyboard::isKeyPressed(Keys[i]->KEY)) {
			if (Keys[i]->KeyState & EnumKeyStates::KeyNotPressed) {
				Keys[i]->KeyState = (EnumKeyStates)(KeyPressed | KeyHold);
				std::printf("Pressed");
				continue;
			}
			else if (Keys[i]->KeyState & EnumKeyStates::KeyPressed) {
				Keys[i]->KeyState = KeyHold;
				std::printf("Hold");
				continue;
			}
		}
		else
		{
			if (Keys[i]->KeyState & EnumKeyStates::KeyHold || Keys[i]->KeyState & EnumKeyStates::KeyPressed || Keys[i]->KeyState & (EnumKeyStates)(KeyPressed | KeyHold)) {
				Keys[i]->KeyState = KeyReleased;
				std::printf("Released");
				continue;
			}
			Keys[i]->KeyState = KeyNotPressed;
			continue;
		}
	}
}

inline Keyboard::Keyboard() {

}

inline Keyboard::~Keyboard() {
}
#pragma endregion
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
#pragma region Mouse definitions
inline Mouse* InputSystem::GetMouseClass() {
	return InputSystem::_mouseClass;
}

inline void Mouse::UpdateMouseState() {
	Mouse::_previousMousePos = Mouse::_currentMousePos;
	Mouse::_currentMousePos = { (float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y };

	Mouse::_mouseDelta = MousePos{ _currentMousePos - _previousMousePos };

	if (Mouse::_mouseDelta != MousePos{0,0}) {
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
		if (sf::Mouse::isButtonPressed(Buttons[i]->KEY)) {
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

inline MousePos Mouse::GetMouseDelta() {
	return _mouseDelta;
}
inline MousePos Mouse::GetMousePos() {
	return _currentMousePos;
}
inline bool Mouse::IsMouseChangePosition() {
	if (Mouse::_mouseDelta == MousePos{ 0,0 }) {
		return false;
	}
	return true;
}

inline Mouse::Mouse() {

}
inline Mouse::~Mouse() {

}

#pragma endregion
//----------------------------------------------------------------------------//