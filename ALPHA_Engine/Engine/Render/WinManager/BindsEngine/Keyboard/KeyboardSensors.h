#pragma once
#include "Render/WinManager/BindsEngine/GeneralSensors.h"
#include <cstdint>
#include <memory>

namespace Render::WindowsManager::BindsEngine {
	class Keyboard;
}

namespace Render::WindowsManager::BindsEngine {

enum class EnumKeyboardTable : uint16_t {
		//In reality, it's a GLFW keymap. Never mind

		A = 65, B = 66, C = 67, D = 68, E = 69, F = 70, G = 71, H = 72, I = 73,
		J = 74, K = 75, L = 76, M = 77, N = 78, O = 79, P = 80, Q = 81, R = 82,
		S = 83, T = 84, U = 85, V = 86, W = 87, X = 88, Y = 89, Z = 90,

	    Num0 = 48, Num1 = 49, Num2 = 50, Num3 = 51, Num4 = 52,
	    Num5 = 53, Num6 = 54, Num7 = 55, Num8 = 56, Num9 = 57,

	    Escape = 256, LControl = 341, LShift = 340, LAlt = 342,
	    RControl = 345, RShift = 344, RAlt = 346, Menu = 348,

	    LBracket = 91, RBracket = 93, Semicolon = 59, Comma = 44,
		Period = 46, Quote = 44, Slash = 47, Backslash = 92,
	    Tilde = 96, Equal = 61, Hyphen = 39, Space = 32,

		Enter = 257, Backspace = 259, Tab = 258,

	    PageUp = 266, PageDown = 267, End = 269, Home = 268,

		Insert = 260, Delete = 261, Add = 334,
	    Subtract = 333, Multiply = 332, Divide = 331,

	    Left = 263, Right = 262, Up = 265, Down = 264,

	    Numpad0 = 320, Numpad1 = 321, Numpad2 = 322, Numpad3 = 323, Numpad4 = 324,
	    Numpad5 = 325, Numpad6 = 326, Numpad7 = 327, Numpad8 = 328, Numpad9 = 329,

		F1 = 290, F2 = 291, F3 = 292, F4 = 293, F5 = 294,
	    F6 = 295, F7 = 296, F8 = 297, F9 = 298, F10 = 299,
	    F11 = 300, F12 = 301, F13 = 302, F14 = 303, F15 = 304,
		Pause = 284
	};

class KeyboardKey
{
	friend Keyboard;
public:
    ///Definition of key by glfw3 representation
    const EnumKeyboardTable KEY;

private:
	///Key state enum
	EnumKeyStates KeyState;

	//16 bits for key needed because I use glfw representation
public:
	KeyboardKey(const uint16_t key) : KEY(static_cast<EnumKeyboardTable>(key)) {}
	~KeyboardKey() = default;
};

class KeyboardData{
	friend class Keyboard;

private:
	KeyboardData();

public:
	KeyboardKey A;						  KeyboardKey B;
	KeyboardKey C;						  KeyboardKey D;
	KeyboardKey E;						  KeyboardKey F;
	KeyboardKey G;						  KeyboardKey H;
	KeyboardKey I;						  KeyboardKey J;
	KeyboardKey K;						  KeyboardKey L;
	KeyboardKey M;						  KeyboardKey N;
	KeyboardKey O;						  KeyboardKey P;
	KeyboardKey Q;						  KeyboardKey R;
	KeyboardKey S;						  KeyboardKey T;
	KeyboardKey U;						  KeyboardKey V;
	KeyboardKey W;						  KeyboardKey X;
	KeyboardKey Y;						  KeyboardKey Z;

	KeyboardKey Num0;					  KeyboardKey Num1;
	KeyboardKey Num2;					  KeyboardKey Num3;
	KeyboardKey Num4;					  KeyboardKey Num5;
	KeyboardKey Num6;					  KeyboardKey Num7;
	KeyboardKey Num8;					  KeyboardKey Num9;

	KeyboardKey Escape;

	KeyboardKey LControl;				  KeyboardKey LShift;
	KeyboardKey LAlt;

	KeyboardKey RControl;				  KeyboardKey RShift;
	KeyboardKey RAlt;

	KeyboardKey Menu;					  KeyboardKey LBracket;
	KeyboardKey RBracket;				  KeyboardKey Semicolon;
	KeyboardKey Comma;				      KeyboardKey Period;
	KeyboardKey Quote;				      KeyboardKey Slash;
	KeyboardKey Backslash;	              KeyboardKey Tilde;
	KeyboardKey Equal;					  KeyboardKey Hyphen;

	KeyboardKey Space;					  KeyboardKey Enter;
	KeyboardKey Backspace;	              KeyboardKey Tab;

	KeyboardKey PageUp;				      KeyboardKey PageDown;
	KeyboardKey End;					  KeyboardKey Home;

	KeyboardKey Insert;				      KeyboardKey Delete;

	KeyboardKey Add;					  KeyboardKey Subtract;
	KeyboardKey Multiply;			      KeyboardKey Divide;

	KeyboardKey Left;					  KeyboardKey Right;
	KeyboardKey Up;						  KeyboardKey Down;

	KeyboardKey Numpad0;		          KeyboardKey Numpad1;
	KeyboardKey Numpad2;		          KeyboardKey Numpad3;
	KeyboardKey Numpad4;		          KeyboardKey Numpad5;
	KeyboardKey Numpad6;		          KeyboardKey Numpad7;
	KeyboardKey Numpad8;		          KeyboardKey Numpad9;

	KeyboardKey F1;						  KeyboardKey F2;
	KeyboardKey F3;						  KeyboardKey F4;
	KeyboardKey F5;						  KeyboardKey F6;
	KeyboardKey F7;						  KeyboardKey F8;
	KeyboardKey F9;						  KeyboardKey F10;
	KeyboardKey F11;					  KeyboardKey F12;
	KeyboardKey F13;					  KeyboardKey F14;
	KeyboardKey F15;

	KeyboardKey Pause;

private:
	std::shared_ptr<std::array<KeyboardKey*,99>> Keys;

public:
	static KeyboardData* GetInstance();
};

}
