#pragma once

#include "Basical_Type.h"
#include "Graphic_Engine.h"

//SFML
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

enum EnumKeyStates {
	KeyNotPressed = 1 << 0,
	KeyPressed = 1 << 1,
	KeyHold = 1 << 2,
	KeyReleased = 1 << 3
};

struct Key
{
	const sf::Keyboard::Key Key;
	EnumKeyStates KeyState;
};

class Keyboard {

#pragma region Keys Definition
	Key A{ sf::Keyboard::A }; Key B{ sf::Keyboard::B };
	Key C{ sf::Keyboard::C }; Key D{ sf::Keyboard::D };
	Key E{ sf::Keyboard::E }; Key F{ sf::Keyboard::F };
	Key G{ sf::Keyboard::G }; Key H{ sf::Keyboard::H };
	Key I{ sf::Keyboard::I }; Key J{ sf::Keyboard::J };
	Key K{ sf::Keyboard::K }; Key L{ sf::Keyboard::L };
	Key M{ sf::Keyboard::M }; Key N{ sf::Keyboard::N };
	Key O{ sf::Keyboard::O }; Key P{ sf::Keyboard::P };
	Key Q{ sf::Keyboard::Q }; Key R{ sf::Keyboard::R };
	Key S{ sf::Keyboard::S }; Key T{ sf::Keyboard::T };
	Key U{ sf::Keyboard::U }; Key V{ sf::Keyboard::V };
	Key W{ sf::Keyboard::W }; Key X{ sf::Keyboard::X };
	Key Y{ sf::Keyboard::Y }; Key Z{ sf::Keyboard::Z };

	Key Num0{ sf::Keyboard::Num0 }; Key Num1{ sf::Keyboard::Num1 };
	Key Num2{ sf::Keyboard::Num2 }; Key Num3{ sf::Keyboard::Num3 };
	Key Num4{ sf::Keyboard::Num4 }; Key Num5{ sf::Keyboard::Num5 };
	Key Num6{ sf::Keyboard::Num6 }; Key Num7{ sf::Keyboard::Num7 };
	Key Num8{ sf::Keyboard::Num8 }; Key Num9{ sf::Keyboard::Num9 };

	Key Escape{ sf::Keyboard::Escape };
	
	Key LControl{ sf::Keyboard::LControl }; Key LShift{ sf::Keyboard::LShift };
	Key LAlt{ sf::Keyboard::LAlt }; Key LSystem{ sf::Keyboard::LSystem };
	
	Key RControl{ sf::Keyboard::RControl }; Key RShift{ sf::Keyboard::RShift };
	Key RAlt{ sf::Keyboard::RAlt }; Key RSystem{ sf::Keyboard::RSystem };
	
	Key Menu{ sf::Keyboard::Menu }; Key LBracket{ sf::Keyboard::LBracket };
	Key RBracket{ sf::Keyboard::RBracket }; Key Semicolon{ sf::Keyboard::Semicolon };
	Key Comma{ sf::Keyboard::Comma }; Key Period{ sf::Keyboard::Period };
	Key Quote{ sf::Keyboard::Quote }; Key Slash{ sf::Keyboard::Slash };
	Key Backslash { sf::Keyboard::Backslash }; Key Tilde{ sf::Keyboard::Tilde };
	Key Equal{ sf::Keyboard::Equal }; Key Hyphen{ sf::Keyboard::Hyphen };
	
	Key Space{ sf::Keyboard::Space }; Key Enter{ sf::Keyboard::Enter };
	Key Backspace{ sf::Keyboard::Backspace }; Key Tab{ sf::Keyboard::Tab };
	
	Key PageUp{ sf::Keyboard::PageUp }; Key PageDown{ sf::Keyboard::PageDown };
	Key End{ sf::Keyboard::End }; Key Home{ sf::Keyboard::Home };
	
	Key Insert{ sf::Keyboard::Insert }; Key Delete{ sf::Keyboard::Delete };
	
	Key Add{ sf::Keyboard::Add }; Key Subtract{ sf::Keyboard::Subtract };
	Key Multiply{ sf::Keyboard::Multiply }; Key Divide{ sf::Keyboard::Divide };

	Key Left{ sf::Keyboard::Left }; Key Right{ sf::Keyboard::Right };
	Key Up{ sf::Keyboard::Up }; Key Down{ sf::Keyboard::Down };

	Key Numpad0{ sf::Keyboard::Numpad0 }; Key Numpad1{ sf::Keyboard::Numpad1 };
	Key Numpad2{ sf::Keyboard::Numpad2 }; Key Numpad3{ sf::Keyboard::Numpad3 };
	Key Numpad4{ sf::Keyboard::Numpad4 }; Key Numpad5{ sf::Keyboard::Numpad5 };
	Key Numpad6{ sf::Keyboard::Numpad6 }; Key Numpad7{ sf::Keyboard::Numpad7 };
	Key Numpad8{ sf::Keyboard::Numpad8 }; Key Numpad9{ sf::Keyboard::Numpad9 };

	Key F1{ sf::Keyboard::F1 }; Key F2{ sf::Keyboard::F2 };
	Key F3{ sf::Keyboard::F3 }; Key F4{ sf::Keyboard::F4 };
	Key F5{ sf::Keyboard::F5 }; Key F6{ sf::Keyboard::F6 };
	Key F7{ sf::Keyboard::F7 }; Key F8{ sf::Keyboard::F8 };
	Key F9{ sf::Keyboard::F9 }; Key F10{ sf::Keyboard::F10 };
	Key F11{ sf::Keyboard::F11 }; Key F12{ sf::Keyboard::F12 };
	Key F13{ sf::Keyboard::F13 }; Key F14{ sf::Keyboard::F14 };
	Key F15{ sf::Keyboard::F15 };

	Key Pause{ sf::Keyboard::Pause };

	Key* Keys[103] = {
		&A, &B, &C, &D,
		&E,&F, &G, &H,
		&I, &J, &K, &L,
		&M, &N, &O, &P,
		&Q, &R, &S, &T,
		&U, &V, &W, &X,
		&Y, &Z, &Num0, &Num1 ,
		&Num2 , &Num3 ,&Num5 , &Num7,
		&Num2 ,&Num3 ,&Num5 ,&Num7,
		&Num8 ,&Num9  ,&Escape  ,&LControl,
		&LShift  ,&LAlt  ,&LSystem  ,&RControl,
		&RShift  ,&RAlt  ,&RSystem  ,&Menu  ,
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
};

class Mouse {
private:
	Vector3 _previousMousePos{ 0,0,0 };
	Vector3 _currentMousePos{ 0,0,0 };
	Vector3 _mouseDelta{ 0,0,0 };

private:
	friend class InputSystem;

public:
	Vector3 GetMousePos();
	Vector3 GetMouseDelta();
	bool IsMouseChangePosition();

private:
	void UpdateMouseInfo();


	inline bool Mouse_Events();
};

class Bind {
public:
	std::vector<void(*)()> Operations;

	std::vector<EnumKeyStates> KeysState{};
	std::vector<sf::Keyboard::Key> KeyboardKeys;
	sf::Mouse::Button MouseKey;

private:
	friend class InputSystem;

private:
	void InvokeOperations();


public:
	Bind(std::vector<void(*)()> Operations,
		std::vector<EnumKeyStates> KeysState = {},
		std::vector<sf::Keyboard::Key> KeyboardKeys = {},
		sf::Mouse::Button MouseKey = (sf::Mouse::Button)(-1));
};

class InputSystem {
private:
	std::vector<Bind> BindsBuff;
	sf::Event Event;

public:
	Screen* ScreenClass;

private:
	Mouse* MouseClass = new Mouse;
	Keyboard* KeyboardClass = new Keyboard;

public:
	inline void IO_Events();

public:
	inline void ClearBindsBuffer();
	inline void InsertBindWithClear(Bind bind);
	inline void InsertBind(Bind bind);

	inline Mouse* GetMouseClass();
};