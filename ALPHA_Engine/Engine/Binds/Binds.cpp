#include "Binds.h"


//----------------------------------------------------------------------------//
#pragma region Bind definitions

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

//---------------------------------------------------------------//
#pragma region General constructor
void Bind::GeneralBind(std::vector<void(*)()> Operations,
	std::vector<EnumKeyStates> KeysState,
	std::vector<uint16_t> KeyboardKeys,
	std::vector<EnumKeyStates> MouseKeysState,
	std::vector<uint8_t> MouseKeys,
	EnumMouseSensorStates MouseSensorState) {

	Bind::Constructor(Operations, KeysState, KeyboardKeys, MouseKeysState, MouseKeys, MouseSensorState);
}
#pragma endregion
//---------------------------------------------------------------//



//---------------------------------------------------------------//
#pragma region Constructor for keyboard bind
void Bind::KeyboardBind(std::vector<void(*)()> Operations,
	std::vector<EnumKeyStates> KeysState,
	std::vector<uint16_t> KeyboardKeys) {

	Bind::Constructor(Operations, KeysState, KeyboardKeys, {}, {}, (EnumMouseSensorStates)(1));
}
#pragma endregion
//---------------------------------------------------------------//


//---------------------------------------------------------------//
#pragma region Constructor for mouse buttons bind
void Bind::MouseButtonsBind(std::vector<void(*)()> Operations,
	std::vector<EnumKeyStates> MouseKeysState,
	std::vector<uint8_t> MouseKeys) {

	Bind::Constructor(Operations, {}, {}, MouseKeysState, MouseKeys, (EnumMouseSensorStates)(1));
}
#pragma endregion
//---------------------------------------------------------------//


//---------------------------------------------------------------//
#pragma region Constructor for mouse sensor bind
void Bind::MouseSensorBind(std::vector<void(*)()> Operations,
	EnumMouseSensorStates MouseSensorState) {

	Bind::Constructor(Operations, {}, {}, {}, {}, MouseSensorState);
}
#pragma endregion
//---------------------------------------------------------------//

void Bind::InvokeOperations() {
	for (size_t i = 0; i < Bind::_operations.size(); i++)
	{
		Bind::_operations[i]();
	}
}
#pragma endregion
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
#pragma region InputSystem definitions
void InputSystem::IO_Events() {
	if (!InputSystem::Window) { return; }

	InputSystem::_mouseClass->UpdateMouseState(*InputSystem::Window);
	InputSystem::_keyboardClass->UpdateKeysState(*InputSystem::Window);

	//if (!InputSystem::Screen->isOpen()) { return; }
	//if (InputSystem::Screen->pollEvent(InputSystem::_event)) { }


	//All values
	for (size_t i = 0; i < InputSystem::_bindsBuff.size(); i++)
	{
		if (InputSystem::_bindsBuff[i].Active == false) { continue; }
		bool mark = true;

		//Keyboard statement check
		for (size_t j = 0; j < InputSystem::_bindsBuff[i]._keyboardKeys.size(); j++)
		{
			EnumKeyStates state = InputSystem::_keyboardClass->GetKeyState(InputSystem::_bindsBuff[i]._keyboardKeys[j]);
			if (! (InputSystem::_bindsBuff[i]._keyboardKeysState[j] & state)) { mark = false; break; }
		}

		//Mouse button statement check
		for (size_t j = 0; j < InputSystem::_bindsBuff[i]._mouseKeys.size(); j++)
		{
			int IdCurrentKey = InputSystem::_bindsBuff[i]._mouseKeys[j];
			if (!(InputSystem::_bindsBuff[i]._mouseKeysState[j] & InputSystem::_mouseClass->Buttons[IdCurrentKey]->KeyState)) { mark = false; break; }
		}		

		//Check mouse sensor statement
		if(InputSystem::_bindsBuff[i]._mouseSensorState & UnknownState) {}
		else if (!(InputSystem::_bindsBuff[i]._mouseSensorState & InputSystem::_mouseClass->MoveSensorState)) { mark = false; }

		if (mark) { InputSystem::_bindsBuff[i].InvokeOperations(); }
	}
}

void InputSystem::ClearBindsBuffer() {
	InputSystem::_bindsBuff.clear();
}
void InputSystem::InsertBindWithClear(Bind bind) {
	ClearBindsBuffer();
	InputSystem::_bindsBuff.push_back(bind);
}
void InputSystem::InsertBind(Bind bind) {
	InputSystem::_bindsBuff.push_back(bind);
}

InputSystem::InputSystem() {
	InputSystem::Window = Window;
}
InputSystem::~InputSystem() {

}
#pragma endregion
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
#pragma region Keyboard definitions
EnumKeyStates Keyboard::GetKeyState(uint16_t key) {
	for (size_t i = 0; i < 99; i++)
	{
		if (Keys[i]->KEY == key) { return Keys[i]->KeyState; }
	}
	return EnumKeyStates::Unknown;
}

void Keyboard::UpdateKeysState(GLFWwindow& window) {
	for (size_t i = 0; i < 99; i++)
	{		
		if (glfwGetKey(&window, Keys[i]->KEY)) {
			if (Keys[i]->KeyState & EnumKeyStates::KeyNotPressed) {
				Keys[i]->KeyState = KeyPressed;
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
			if (Keys[i]->KeyState & EnumKeyStates::KeyHold || Keys[i]->KeyState & EnumKeyStates::KeyPressed) {
				Keys[i]->KeyState = KeyReleased;
				std::printf("Released");
				continue;
			}
			Keys[i]->KeyState = KeyNotPressed;
			continue;
		}
	}
}

Keyboard::Keyboard() {

}

Keyboard::~Keyboard() {
}
#pragma endregion
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
#pragma region Mouse definitions
Mouse* InputSystem::GetMouseClass() {
	return InputSystem::_mouseClass;
}

void Mouse::UpdateMouseState(GLFWwindow& window) {
	double xpos, ypos;
	glfwGetCursorPos(&window, &xpos, &ypos);

	Mouse::_previousMousePos = Mouse::_currentMousePos;
	Mouse::_currentMousePos = { (float)xpos, (float)ypos };

	Mouse::_mouseDelta = MousePos{ _currentMousePos - _previousMousePos };

	if (Mouse::_mouseDelta != MousePos{0,0}) {
		if (Mouse::MoveSensorState & MouseNotMoved || Mouse::MoveSensorState & MouseEndMoved) {
			Mouse::MoveSensorState = MouseStartMoved;
		}
		else if (Mouse::MoveSensorState & MouseStartMoved) {
			Mouse::MoveSensorState = MouseKeepMoved;
		}
	}
	else
	{
		if (Mouse::MoveSensorState & MouseKeepMoved || Mouse::MoveSensorState & MouseStartMoved) {
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
		
		if (glfwGetMouseButton(&window, Buttons[i]->KEY)) {
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

MousePos Mouse::GetMouseDelta() {
	return _mouseDelta;
}
MousePos Mouse::GetMousePos() {
	return _currentMousePos;
}
bool Mouse::IsMouseChangePosition() {
	if (Mouse::_mouseDelta == MousePos{ 0,0 }) {
		return false;
	}
	return true;
}

Mouse::Mouse() {

}
Mouse::~Mouse() {

}

#pragma endregion
//----------------------------------------------------------------------------//