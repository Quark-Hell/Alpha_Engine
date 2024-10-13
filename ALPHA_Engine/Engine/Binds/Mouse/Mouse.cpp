#include "Mouse.h"
#include "Binds/GeneralSensors.h"

namespace BindsEngine {

Mouse::Mouse() = default;
Mouse::~Mouse() = default;

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

MousePos BindsEngine::Mouse::GetMouseDelta() {
	return _mouseDelta;
}
MousePos BindsEngine::Mouse::GetMousePos() {
	return _currentMousePos;
}
bool Mouse::IsMouseChangePosition() {
	if (Mouse::_mouseDelta == MousePos{ 0,0 }) {
		return false;
	}
	return true;
}

}