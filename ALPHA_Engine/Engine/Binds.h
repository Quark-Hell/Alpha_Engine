#pragma once

//SFML
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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

	inline MousePos(float XPos = 0, float YPos = 0) {
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
	* Definition of key by sfml representation
	* Example:
	* sf::Keyboard::A
	*/
	const sf::Keyboard::Key KEY;

	/*
	* Key state enum
	*/
	EnumKeyStates KeyState;
};
class Keyboard {

#pragma region Keys Definition
private:
	KeyboardKey A{ sf::Keyboard::A };								KeyboardKey B{ sf::Keyboard::B };
	KeyboardKey C{ sf::Keyboard::C };								KeyboardKey D{ sf::Keyboard::D };
	KeyboardKey E{ sf::Keyboard::E };								KeyboardKey F{ sf::Keyboard::F };
	KeyboardKey G{ sf::Keyboard::G };								KeyboardKey H{ sf::Keyboard::H };
	KeyboardKey I{ sf::Keyboard::I };								KeyboardKey J{ sf::Keyboard::J };
	KeyboardKey K{ sf::Keyboard::K };								KeyboardKey L{ sf::Keyboard::L };
	KeyboardKey M{ sf::Keyboard::M };								KeyboardKey N{ sf::Keyboard::N };
	KeyboardKey O{ sf::Keyboard::O };								KeyboardKey P{ sf::Keyboard::P };
	KeyboardKey Q{ sf::Keyboard::Q };								KeyboardKey R{ sf::Keyboard::R };
	KeyboardKey S{ sf::Keyboard::S };								KeyboardKey T{ sf::Keyboard::T };
	KeyboardKey U{ sf::Keyboard::U };								KeyboardKey V{ sf::Keyboard::V };
	KeyboardKey W{ sf::Keyboard::W };								KeyboardKey X{ sf::Keyboard::X };
	KeyboardKey Y{ sf::Keyboard::Y };								KeyboardKey Z{ sf::Keyboard::Z };

	KeyboardKey Num0{ sf::Keyboard::Num0 };					KeyboardKey Num1{ sf::Keyboard::Num1 };
	KeyboardKey Num2{ sf::Keyboard::Num2 };					KeyboardKey Num3{ sf::Keyboard::Num3 };
	KeyboardKey Num4{ sf::Keyboard::Num4 };					KeyboardKey Num5{ sf::Keyboard::Num5 };
	KeyboardKey Num6{ sf::Keyboard::Num6 };					KeyboardKey Num7{ sf::Keyboard::Num7 };
	KeyboardKey Num8{ sf::Keyboard::Num8 };					KeyboardKey Num9{ sf::Keyboard::Num9 };

	KeyboardKey Escape{ sf::Keyboard::Escape };
	
	KeyboardKey LControl{ sf::Keyboard::LControl };			KeyboardKey LShift{ sf::Keyboard::LShift };
	KeyboardKey LAlt{ sf::Keyboard::LAlt };						KeyboardKey LSystem{ sf::Keyboard::LSystem };
	
	KeyboardKey RControl{ sf::Keyboard::RControl };			KeyboardKey RShift{ sf::Keyboard::RShift };
	KeyboardKey RAlt{ sf::Keyboard::RAlt };						KeyboardKey RSystem{ sf::Keyboard::RSystem };
	
	KeyboardKey Menu{ sf::Keyboard::Menu };					KeyboardKey LBracket{ sf::Keyboard::LBracket };
	KeyboardKey RBracket{ sf::Keyboard::RBracket };		KeyboardKey Semicolon{ sf::Keyboard::Semicolon };
	KeyboardKey Comma{ sf::Keyboard::Comma };				KeyboardKey Period{ sf::Keyboard::Period };
	KeyboardKey Quote{ sf::Keyboard::Quote };				KeyboardKey Slash{ sf::Keyboard::Slash };
	KeyboardKey Backslash { sf::Keyboard::Backslash };	KeyboardKey Tilde{ sf::Keyboard::Tilde };
	KeyboardKey Equal{ sf::Keyboard::Equal };					KeyboardKey Hyphen{ sf::Keyboard::Hyphen };
	
	KeyboardKey Space{ sf::Keyboard::Space };					KeyboardKey Enter{ sf::Keyboard::Enter };
	KeyboardKey Backspace{ sf::Keyboard::Backspace };	KeyboardKey Tab{ sf::Keyboard::Tab };
	
	KeyboardKey PageUp{ sf::Keyboard::PageUp };				KeyboardKey PageDown{ sf::Keyboard::PageDown };
	KeyboardKey End{ sf::Keyboard::End };						KeyboardKey Home{ sf::Keyboard::Home };
	
	KeyboardKey Insert{ sf::Keyboard::Insert };				 KeyboardKey Delete{ sf::Keyboard::Delete };
	
	KeyboardKey Add{ sf::Keyboard::Add };						KeyboardKey Subtract{ sf::Keyboard::Subtract };
	KeyboardKey Multiply{ sf::Keyboard::Multiply };			KeyboardKey Divide{ sf::Keyboard::Divide };

	KeyboardKey Left{ sf::Keyboard::Left };						KeyboardKey Right{ sf::Keyboard::Right };
	KeyboardKey Up{ sf::Keyboard::Up };							KeyboardKey Down{ sf::Keyboard::Down };

	KeyboardKey Numpad0{ sf::Keyboard::Numpad0 };		KeyboardKey Numpad1{ sf::Keyboard::Numpad1 };
	KeyboardKey Numpad2{ sf::Keyboard::Numpad2 };		KeyboardKey Numpad3{ sf::Keyboard::Numpad3 };
	KeyboardKey Numpad4{ sf::Keyboard::Numpad4 };		KeyboardKey Numpad5{ sf::Keyboard::Numpad5 };
	KeyboardKey Numpad6{ sf::Keyboard::Numpad6 };		KeyboardKey Numpad7{ sf::Keyboard::Numpad7 };
	KeyboardKey Numpad8{ sf::Keyboard::Numpad8 };		KeyboardKey Numpad9{ sf::Keyboard::Numpad9 };

	KeyboardKey F1{ sf::Keyboard::F1 };								KeyboardKey F2{ sf::Keyboard::F2 };
	KeyboardKey F3{ sf::Keyboard::F3 };							KeyboardKey F4{ sf::Keyboard::F4 };
	KeyboardKey F5{ sf::Keyboard::F5 };							KeyboardKey F6{ sf::Keyboard::F6 };
	KeyboardKey F7{ sf::Keyboard::F7 };							KeyboardKey F8{ sf::Keyboard::F8 };
	KeyboardKey F9{ sf::Keyboard::F9 };							KeyboardKey F10{ sf::Keyboard::F10 };
	KeyboardKey F11{ sf::Keyboard::F11 };							KeyboardKey F12{ sf::Keyboard::F12 };
	KeyboardKey F13{ sf::Keyboard::F13 };							KeyboardKey F14{ sf::Keyboard::F14 };
	KeyboardKey F15{ sf::Keyboard::F15 };

	KeyboardKey Pause{ sf::Keyboard::Pause };

private:
	KeyboardKey* Keys[101] = {
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
		&LSystem  ,&RControl, &RShift  ,&RAlt,
		&RSystem  ,&Menu  ,
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
	inline void UpdateKeysState();

public:
	inline Keyboard();
	inline ~Keyboard();
};

struct MouseKey
{
	/*
	* Definition of key by sfml representation
	* Example:
	* sf::Mouse::Left
	*/
	const sf::Mouse::Button KEY;
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
	MouseKey _leftButton{sf::Mouse::Left};
	MouseKey _rightButton{ sf::Mouse::Right };
	MouseKey _middleButton{ sf::Mouse::Middle };

	MouseKey _firstExtraButton{ sf::Mouse::XButton1 };
	MouseKey _secondExtraButton{ sf::Mouse::XButton2 };

	EnumMouseSensorStates MoveSensorState;

	MouseKey* Buttons[5] = {
		&_leftButton, &_rightButton,
		&_middleButton, &_firstExtraButton,
		&_secondExtraButton
	};

private:
	friend class InputSystem;

public:
	inline MousePos GetMousePos();
	inline MousePos GetMouseDelta();
	inline bool IsMouseChangePosition();

	Mouse();
	~Mouse();

private:
	inline void UpdateMouseState();
};

class Bind {
private:
	std::vector<void(*)()> _operations;

	sf::Event::EventType _eventType;
	std::vector<EnumKeyStates> _keyboardKeysState;
	std::vector<sf::Keyboard::Key> _keyboardKeys;
	std::vector<EnumKeyStates> _mouseKeysState;
	std::vector<sf::Mouse::Button> _mouseKeys;
	EnumMouseSensorStates _mouseSensorState;

private:
	friend class InputSystem;

private:
	void InvokeOperations();
	void Constructor(std::vector<void(*)()> Operations = {},
		std::vector<EnumKeyStates> KeysState = {},
		std::vector<sf::Keyboard::Key> KeyboardKeys = {},
		std::vector<EnumKeyStates> MouseKeysState = {},
		std::vector<sf::Mouse::Button> MouseKeys = {},
		EnumMouseSensorStates MouseSensorState = (EnumMouseSensorStates)(1),
		sf::Event::EventType EventType = (sf::Event::EventType)(-1));


	//----------------------------------------------------------------------------//
#pragma region General constructor
public:
	void GeneralBind(std::vector<void(*)()> Operations,
		std::vector<EnumKeyStates> KeysState,
		std::vector<sf::Keyboard::Key> KeyboardKeys,
		std::vector<EnumKeyStates> MouseKeysState,
		std::vector<sf::Mouse::Button> MouseKeys,
		EnumMouseSensorStates MouseSensorState,
		sf::Event::EventType EventType);
#pragma endregion
	//----------------------------------------------------------------------------//



	//----------------------------------------------------------------------------//
#pragma region Constructor for keyboard bind
public:
	void KeyboardBind(std::vector<void(*)()> Operations,
		std::vector<EnumKeyStates> KeysState,
		std::vector<sf::Keyboard::Key> KeyboardKeys,
		sf::Event::EventType EventType);

public:
	void KeyboardBind(std::vector<void(*)()> Operations,
		std::vector<EnumKeyStates> KeysState,
		std::vector<sf::Keyboard::Key> KeyboardKeys);
#pragma endregion
	//----------------------------------------------------------------------------//



	//----------------------------------------------------------------------------//
#pragma region Constructor for mouse buttons bind
public:
	void MouseButtonsBind(std::vector<void(*)()> Operations,
		std::vector<EnumKeyStates> MouseKeysState,
		std::vector<sf::Mouse::Button> MouseKeys,
		sf::Event::EventType EventType);

public:
	void MouseButtonsBind(std::vector<void(*)()> Operations,
		std::vector<EnumKeyStates> MouseKeysState,
		std::vector<sf::Mouse::Button> MouseKeys);
#pragma endregion
	//----------------------------------------------------------------------------//



	//----------------------------------------------------------------------------//
#pragma region Constructor for mouse sensor bind
public:
	void MouseSensorBind(std::vector<void(*)()> Operations,
		EnumMouseSensorStates MouseSensorState,
		sf::Event::EventType EventType);

public:
	void MouseSensorBind(std::vector<void(*)()> Operations,
		EnumMouseSensorStates MouseSensorState);
#pragma endregion
	//----------------------------------------------------------------------------//
};

class InputSystem {
private:
	std::vector<Bind> _bindsBuff;
	sf::Event _event;

	Mouse* _mouseClass = new Mouse;
	Keyboard* _keyboardClass = new Keyboard;

public:
	sf::RenderWindow* Screen;

public:
	void IO_Events();

	void ClearBindsBuffer();
	void InsertBindWithClear(Bind bind);
	void InsertBind(Bind bind);

	Mouse* GetMouseClass();

	InputSystem();
	~InputSystem();
};