#pragma once

#include "Basical_Type.h"

#include <GLFW/glfw3.h>

struct MousePos {
public:
	float XPos = 0;
	float YPos = 0;

public:
	void SetMousePos(MousePos MousePos) {
		MousePos::XPos = MousePos.XPos;
		MousePos::YPos = MousePos.YPos;
	}
	MousePos GetMousePos() {
		return(MousePos{XPos,YPos});
	}

	MousePos(float XPos = 0, float YPos = 0) {
		MousePos::XPos = XPos;
		MousePos::YPos = YPos;
	}

#pragma region Operators overload
	//-----------------------------------------------------------//
	void operator=(const MousePos value) {
		XPos = value.XPos;
		YPos = value.YPos;
	}
	void operator=(const MousePos* value) {
		XPos = value->XPos;
		YPos = value->YPos;
	}

	void operator=(const float value) {
		XPos = value;
		YPos = value;
	}
	void operator=(const float* value) {
		XPos = *value;
		YPos = *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	MousePos operator+(const MousePos value) {
		return MousePos(XPos + value.XPos, YPos + value.YPos);
	}
	MousePos operator+(const MousePos* value) {
		return MousePos(XPos + value->XPos, YPos + value->YPos);
	}

	MousePos operator+(const float value) {
		return MousePos(XPos + value, YPos + value);
	}
	MousePos operator+(const float* value) {
		return MousePos(XPos + *value, YPos + *value);
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	MousePos operator-(const MousePos value) {
		return MousePos(XPos - value.XPos, YPos - value.YPos);
	}
	MousePos operator-(const MousePos* value) {
		return MousePos(XPos - value->XPos, YPos - value->YPos);
	}

	MousePos operator-(const float value) {
		return MousePos(XPos - value, YPos - value);
	}
	MousePos operator-(const float* value) {
		return MousePos(XPos - *value, YPos - *value);
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	MousePos operator*(const MousePos value) {
		return MousePos(XPos * value.XPos, YPos * value.YPos);
	}
	MousePos operator*(const MousePos* value) {
		return MousePos(XPos * value->XPos, YPos * value->YPos);
	}

	MousePos operator*(const float value) {
		return MousePos(XPos * value, YPos * value);
	}
	MousePos operator*(const float* value) {
		return MousePos(XPos * *value, YPos * *value);
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	MousePos operator/(const MousePos value) {
		return MousePos(XPos / value.XPos, YPos / value.YPos);
	}
	MousePos operator/(const MousePos* value) {
		return MousePos(XPos / value->XPos, YPos / value->XPos);
	}

	MousePos operator/(const float value) {
		return MousePos(XPos / value, YPos / value);
	}
	MousePos operator/(const float* value) {
		return MousePos(XPos / *value, YPos / *value);
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void operator+=(const MousePos value) {
		XPos += value.XPos;
		YPos += value.YPos;
	}
	void operator+=(const MousePos* value) {
		XPos += value->XPos;
		YPos += value->YPos;
	}

	void operator+=(const float value) {
		XPos += value;
		YPos += value;
	}
	void operator+=(const float* value) {
		XPos += *value;
		YPos += *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void operator-=(const MousePos value) {
		XPos -= value.XPos;
		YPos -= value.YPos;
	}
	void operator-=(const MousePos* value) {
		XPos -= value->XPos;
		YPos -= value->YPos;
	}

	void operator-=(const float value) {
		XPos -= value;
		YPos -= value;
	}
	void operator-=(const float* value) {
		XPos -= *value;
		YPos -= *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void operator*=(const MousePos value) {
		XPos *= value.XPos;
		YPos *= value.YPos;
	}
	void operator*=(const MousePos* value) {
		XPos *= value->XPos;
		YPos *= value->YPos;
	}

	void operator*=(const float value) {
		XPos *= value;
		YPos *= value;
	}
	void operator*=(const float* value) {
		XPos *= *value;
		YPos *= *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void operator/=(const MousePos value) {
		XPos /= value.XPos;
		YPos /= value.YPos;
	}
	void operator/=(const MousePos* value) {
		XPos /= value->XPos;
		YPos /= value->YPos;
	}

	void operator/=(const float value) {
		XPos /= value;
		YPos /= value;
	}
	void operator/=(const float* value) {
		XPos /= *value;
		YPos /= *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	bool operator!=(const MousePos value) const {
		if (XPos != value.XPos || YPos != value.YPos)
		{
			return true;
		}
		return false;
	}
	bool operator!=(const MousePos* value) const {
		if (XPos != value->XPos || YPos != value->YPos)
		{
			return true;
		}
		return false;
	}

	bool operator!=(const float value) const {
		if (XPos != value || YPos != value)
		{
			return true;
		}
		return false;
	}
	bool operator!=(const float* value) const {
		if (XPos != *value || YPos != *value)
		{
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	bool operator==(const MousePos value) const {
		if (XPos == value.XPos && YPos == value.YPos)
		{
			return true;
		}
		return false;
	}
	bool operator==(const MousePos* value) const {
		if (XPos == value->XPos && YPos == value->YPos)
		{
			return true;
		}
		return false;
	}

	bool operator==(const float value) const {
		if (XPos == value && YPos == value)
		{
			return true;
		}
		return false;
	}
	bool operator==(const float* value) const {
		if (XPos == *value && YPos == *value)
		{
			return true;
		}
		return false;
	}
	//-----------------------------------------------------------//	
#pragma endregion
};

enum EnumKeyStates {
	Unknown = -1,

	KeyNotPressed = 1 << 0,
	KeyPressed = 1 << 1,
	KeyHold = 1 << 2,
	KeyReleased = 1 << 3,

	MouseWheelStartMoved = 1 << 4,
	MouseWheelKeepMoved = 1 << 5,
	MouseWheelEndMoved = 1 << 6,

	MouseWheelMovedUp = 1 << 7,
	MouseWheelMovedDown = 1 << 8
};

enum EnumMouseSensorStates {
	UnknownState = 1 << 0,

	MouseNotMoved = 1 << 1,
	MouseStartMoved = 1 << 2,
	MouseKeepMoved = 1 << 3,
	MouseEndMoved = 1 << 4,

	MouseEntire = 1 << 5,
	MouseLeft = 1 << 6,
};

struct KeyboardKey
{
	/*
	* Definition of key by glfw3 representation
	*/
	const uint16_t KEY;

	/*
	* Key state enum
	*/
	EnumKeyStates KeyState;
};
class Keyboard {

#pragma region Keys Definition
private:
	KeyboardKey A{ GLFW_KEY_A };								KeyboardKey B{ GLFW_KEY_B };
	KeyboardKey C{ GLFW_KEY_C };								KeyboardKey D{ GLFW_KEY_D };
	KeyboardKey E{ GLFW_KEY_E };								KeyboardKey F{ GLFW_KEY_F };
	KeyboardKey G{ GLFW_KEY_G };								KeyboardKey H{ GLFW_KEY_H };
	KeyboardKey I{ GLFW_KEY_I };								KeyboardKey J{ GLFW_KEY_J };
	KeyboardKey K{ GLFW_KEY_K };								KeyboardKey L{ GLFW_KEY_L };
	KeyboardKey M{ GLFW_KEY_M };								KeyboardKey N{ GLFW_KEY_N };
	KeyboardKey O{ GLFW_KEY_O };								KeyboardKey P{ GLFW_KEY_P };
	KeyboardKey Q{ GLFW_KEY_Q };								KeyboardKey R{ GLFW_KEY_R };
	KeyboardKey S{ GLFW_KEY_S };								KeyboardKey T{ GLFW_KEY_T };
	KeyboardKey U{ GLFW_KEY_U };								KeyboardKey V{ GLFW_KEY_V };
	KeyboardKey W{ GLFW_KEY_W };								KeyboardKey X{ GLFW_KEY_X };
	KeyboardKey Y{ GLFW_KEY_Y };								KeyboardKey Z{ GLFW_KEY_Z };

	KeyboardKey Num0{ GLFW_KEY_0 };					            KeyboardKey Num1{ GLFW_KEY_1 };
	KeyboardKey Num2{ GLFW_KEY_2 };					            KeyboardKey Num3{ GLFW_KEY_3 };
	KeyboardKey Num4{ GLFW_KEY_4 };					            KeyboardKey Num5{ GLFW_KEY_5 };
	KeyboardKey Num6{ GLFW_KEY_6 };					            KeyboardKey Num7{ GLFW_KEY_7 };
	KeyboardKey Num8{ GLFW_KEY_7 };					            KeyboardKey Num9{ GLFW_KEY_9 };

	KeyboardKey Escape{ GLFW_KEY_ESCAPE };
	
	KeyboardKey LControl{ GLFW_KEY_LEFT_CONTROL };			    KeyboardKey LShift{ GLFW_KEY_LEFT_SHIFT };
	KeyboardKey LAlt{ GLFW_KEY_LEFT_ALT };						
	
	KeyboardKey RControl{ GLFW_KEY_RIGHT_CONTROL };			    KeyboardKey RShift{ GLFW_KEY_RIGHT_SHIFT };
	KeyboardKey RAlt{ GLFW_KEY_RIGHT_ALT };						
	
	KeyboardKey Menu{ GLFW_KEY_MENU };					        KeyboardKey LBracket{ GLFW_KEY_LEFT_BRACKET };
	KeyboardKey RBracket{ GLFW_KEY_RIGHT_BRACKET };		        KeyboardKey Semicolon{ GLFW_KEY_SEMICOLON };
	KeyboardKey Comma{ GLFW_KEY_COMMA };				        KeyboardKey Period{ GLFW_KEY_PERIOD };
	KeyboardKey Quote{ GLFW_KEY_COMMA };				        KeyboardKey Slash{ GLFW_KEY_SLASH };
	KeyboardKey Backslash{ GLFW_KEY_BACKSLASH };	            KeyboardKey Tilde{ GLFW_KEY_GRAVE_ACCENT };
	KeyboardKey Equal{ GLFW_KEY_EQUAL };					    KeyboardKey Hyphen{ GLFW_KEY_APOSTROPHE };
	
	KeyboardKey Space{ GLFW_KEY_SPACE };					    KeyboardKey Enter{ GLFW_KEY_ENTER };
	KeyboardKey Backspace{ GLFW_KEY_BACKSPACE };	            KeyboardKey Tab{ GLFW_KEY_TAB };
	
	KeyboardKey PageUp{ GLFW_KEY_PAGE_UP };				        KeyboardKey PageDown{ GLFW_KEY_PAGE_DOWN };
	KeyboardKey End{ GLFW_KEY_END };					 	    KeyboardKey Home{ GLFW_KEY_HOME };
	
	KeyboardKey Insert{ GLFW_KEY_INSERT };				        KeyboardKey Delete{ GLFW_KEY_DELETE };
	
	KeyboardKey Add{ GLFW_KEY_KP_ADD };						    KeyboardKey Subtract{ GLFW_KEY_KP_SUBTRACT };
	KeyboardKey Multiply{ GLFW_KEY_KP_MULTIPLY };			    KeyboardKey Divide{ GLFW_KEY_KP_SUBTRACT };

	KeyboardKey Left{ GLFW_KEY_LEFT };						    KeyboardKey Right{ GLFW_KEY_RIGHT };
	KeyboardKey Up{ GLFW_KEY_UP };							    KeyboardKey Down{ GLFW_KEY_DOWN };
															    
	KeyboardKey Numpad0{ GLFW_KEY_KP_0 };		                KeyboardKey Numpad1{ GLFW_KEY_KP_1 };
	KeyboardKey Numpad2{ GLFW_KEY_KP_2 };		                KeyboardKey Numpad3{ GLFW_KEY_KP_3 };
	KeyboardKey Numpad4{ GLFW_KEY_KP_4 };		                KeyboardKey Numpad5{ GLFW_KEY_KP_5 };
	KeyboardKey Numpad6{ GLFW_KEY_KP_6 };		                KeyboardKey Numpad7{ GLFW_KEY_KP_7 };
	KeyboardKey Numpad8{ GLFW_KEY_KP_8 };		                KeyboardKey Numpad9{ GLFW_KEY_KP_9 };

	KeyboardKey F1{ GLFW_KEY_F1 };								KeyboardKey F2{ GLFW_KEY_F2 };
	KeyboardKey F3{ GLFW_KEY_F3 };							    KeyboardKey F4{ GLFW_KEY_F4 };
	KeyboardKey F5{ GLFW_KEY_F5 };							    KeyboardKey F6{ GLFW_KEY_F6 };
	KeyboardKey F7{ GLFW_KEY_F7 };							    KeyboardKey F8{ GLFW_KEY_F8 };
	KeyboardKey F9{ GLFW_KEY_F9 };							    KeyboardKey F10{ GLFW_KEY_F10 };
	KeyboardKey F11{ GLFW_KEY_F11 };							KeyboardKey F12{ GLFW_KEY_F12 };
	KeyboardKey F13{ GLFW_KEY_F13 };							KeyboardKey F14{ GLFW_KEY_F14 };
	KeyboardKey F15{ GLFW_KEY_F15 };

	KeyboardKey Pause{ GLFW_KEY_PAUSE };

private:
	KeyboardKey* Keys[99] = {
		&A, &B, &C, &D,
		&E,&F, &G, &H,
		&I, &J, &K, &L,
		&M, &N, &O, &P,
		&Q, &R, &S, &T,
		&U, &V, &W, &X,
		&Y, &Z, &Num0, &Num1 ,
		&Num2 , &Num3 ,&Num4 , &Num5,
		&Num6 ,&Num7, &Num8 ,&Num9,
		&Escape  ,&LControl, &LShift  ,&LAlt,
		&RControl, &RShift  ,&RAlt,
		&Menu  ,
		&LBracket  ,&RBracket  ,&Semicolon  ,&Comma  ,
		&Period  ,&Quote  ,&Slash  ,&Backslash  ,
		&Tilde  ,&Equal ,&Hyphen ,&Space,
		&Enter  ,&Backspace  ,&Tab  ,&PageUp,
		&PageDown  ,&End  ,&Home  ,&Insert,
		&Delete  ,&Add  ,&Subtract  ,&Multiply,
		&Divide  ,&Left  ,&Right  ,&Up,
		&Down  ,&Numpad0  ,&Numpad1  ,&Numpad2,
		&Numpad3 ,&Numpad4  ,&Numpad5   ,&Numpad6,
		&Numpad7  ,&Numpad8   ,&Numpad9   ,&F1,
		&F2  ,&F3   ,&F4   ,&F5,
		&F6   ,&F7   ,&F8     ,&F9,
		&F10  ,&F11   ,&F12    ,&F13,
		&F14   ,&F15    ,&Pause
	};
#pragma endregion

private:
	friend class InputSystem;

private:
	EnumKeyStates GetKeyState(uint16_t key);
	void UpdateKeysState(GLFWwindow& window);

public:
	Keyboard();
	~Keyboard();
};

struct MouseKey
{
	/*
	* Definition of key by glfw3 representation
	*/
	const uint8_t KEY;
	/*
	* Key state enum
	*/
	EnumKeyStates KeyState;
};
class Mouse {
private:
	MousePos _previousMousePos;
	MousePos _currentMousePos;
	MousePos _mouseDelta;

private:
	MouseKey _leftButton{ GLFW_MOUSE_BUTTON_LEFT };
	MouseKey _rightButton{ GLFW_MOUSE_BUTTON_RIGHT };
	MouseKey _middleButton{ GLFW_MOUSE_BUTTON_MIDDLE };

	MouseKey _firstExtraButton{ GLFW_MOUSE_BUTTON_4 };
	MouseKey _secondExtraButton{ GLFW_MOUSE_BUTTON_5 };

	EnumMouseSensorStates MoveSensorState;

	MouseKey* Buttons[5] = {
		&_leftButton, &_rightButton,
		&_middleButton, &_firstExtraButton,
		&_secondExtraButton
	};

private:
	friend class InputSystem;

public:
	MousePos GetMousePos();
	MousePos GetMouseDelta();
	bool IsMouseChangePosition();

	Mouse();
	~Mouse();

private:
	void UpdateMouseState(GLFWwindow& window);
};

class Bind {
private:
	std::vector<void(*)()> _operations;

	std::vector<EnumKeyStates> _keyboardKeysState;
	std::vector<uint16_t> _keyboardKeys;
	std::vector<EnumKeyStates> _mouseKeysState;
	std::vector<uint8_t> _mouseKeys;
	EnumMouseSensorStates _mouseSensorState;

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

	//----------------------------------------------------------------------------//
#pragma region General constructor
public:
	void GeneralBind(std::vector<void(*)()> Operations,
		std::vector<EnumKeyStates> KeysState,
		std::vector<uint16_t> KeyboardKeys,
		std::vector<EnumKeyStates> MouseKeysState,
		std::vector<uint8_t> MouseKeys,
		EnumMouseSensorStates MouseSensorState);
#pragma endregion
	//----------------------------------------------------------------------------//



	//----------------------------------------------------------------------------//
#pragma region Constructor for keyboard bind
public:
	void KeyboardBind(
		std::vector<void(*)()> Operations,
		std::vector<EnumKeyStates> KeysState,
		std::vector<uint16_t> KeyboardKeys);
#pragma endregion
	//----------------------------------------------------------------------------//



	//----------------------------------------------------------------------------//
#pragma region Constructor for mouse buttons bind
public:
	void MouseButtonsBind(
		std::vector<void(*)()> Operations,
		std::vector<EnumKeyStates> MouseKeysState,
		std::vector<uint8_t> MouseKeys);
#pragma endregion
	//----------------------------------------------------------------------------//



	//----------------------------------------------------------------------------//
#pragma region Constructor for mouse sensor bind
public:
	void MouseSensorBind(
		std::vector<void(*)()> Operations,
		EnumMouseSensorStates MouseSensorState);
#pragma endregion
	//----------------------------------------------------------------------------//
};

class InputSystem {
private:
	std::vector<Bind> _bindsBuff;

	Mouse* _mouseClass = new Mouse;
	Keyboard* _keyboardClass = new Keyboard;

public:
	GLFWwindow* Window;

public:
	void IO_Events();

	void ClearBindsBuffer();
	void InsertBindWithClear(Bind bind);
	void InsertBind(Bind bind);

	Mouse* GetMouseClass();

	InputSystem();
	~InputSystem();
};