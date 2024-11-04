#pragma once
#include "Render/WinManager/BindsEngine/GeneralSensors.h"
#include <cstdint>
#include "GLFW/glfw3.h"

namespace Render::WindowsManager::BindsEngine {

class KeyboardKey
{
  public:
    ///Definition of key by glfw3 representation
    const uint16_t KEY;
    ///Key state enum
    EnumKeyStates KeyState;

    KeyboardKey(const uint16_t key) : KEY(key) {}
};

class KeyboardData{
  friend class Keyboard;

private:
	static inline KeyboardKey A{ GLFW_KEY_A };								static inline KeyboardKey B{ GLFW_KEY_B };
	static inline KeyboardKey C{ GLFW_KEY_C };								static inline KeyboardKey D{ GLFW_KEY_D };
	static inline KeyboardKey E{ GLFW_KEY_E };								static inline KeyboardKey F{ GLFW_KEY_F };
	static inline KeyboardKey G{ GLFW_KEY_G };								static inline KeyboardKey H{ GLFW_KEY_H };
	static inline KeyboardKey I{ GLFW_KEY_I };								static inline KeyboardKey J{ GLFW_KEY_J };
	static inline KeyboardKey K{ GLFW_KEY_K };								static inline KeyboardKey L{ GLFW_KEY_L };
	static inline KeyboardKey M{ GLFW_KEY_M };								static inline KeyboardKey N{ GLFW_KEY_N };
	static inline KeyboardKey O{ GLFW_KEY_O };								static inline KeyboardKey P{ GLFW_KEY_P };
	static inline KeyboardKey Q{ GLFW_KEY_Q };								static inline KeyboardKey R{ GLFW_KEY_R };
	static inline KeyboardKey S{ GLFW_KEY_S };								static inline KeyboardKey T{ GLFW_KEY_T };
	static inline KeyboardKey U{ GLFW_KEY_U };								static inline KeyboardKey V{ GLFW_KEY_V };
	static inline KeyboardKey W{ GLFW_KEY_W };								static inline KeyboardKey X{ GLFW_KEY_X };
	static inline KeyboardKey Y{ GLFW_KEY_Y };								static inline KeyboardKey Z{ GLFW_KEY_Z };

	static inline KeyboardKey Num0{ GLFW_KEY_0 };					        static inline KeyboardKey Num1{ GLFW_KEY_1 };
	static inline KeyboardKey Num2{ GLFW_KEY_2 };					        static inline KeyboardKey Num3{ GLFW_KEY_3 };
	static inline KeyboardKey Num4{ GLFW_KEY_4 };					        static inline KeyboardKey Num5{ GLFW_KEY_5 };
	static inline KeyboardKey Num6{ GLFW_KEY_6 };					        static inline KeyboardKey Num7{ GLFW_KEY_7 };
	static inline KeyboardKey Num8{ GLFW_KEY_7 };					        static inline KeyboardKey Num9{ GLFW_KEY_9 };

	static inline KeyboardKey Escape{ GLFW_KEY_ESCAPE };

	static inline KeyboardKey LControl{ GLFW_KEY_LEFT_CONTROL };			static inline KeyboardKey LShift{ GLFW_KEY_LEFT_SHIFT };
	static inline KeyboardKey LAlt{ GLFW_KEY_LEFT_ALT };

	static inline KeyboardKey RControl{ GLFW_KEY_RIGHT_CONTROL };			static inline KeyboardKey RShift{ GLFW_KEY_RIGHT_SHIFT };
	static inline KeyboardKey RAlt{ GLFW_KEY_RIGHT_ALT };

	static inline KeyboardKey Menu{ GLFW_KEY_MENU };					    static inline KeyboardKey LBracket{ GLFW_KEY_LEFT_BRACKET };
	static inline KeyboardKey RBracket{ GLFW_KEY_RIGHT_BRACKET };		    static inline KeyboardKey Semicolon{ GLFW_KEY_SEMICOLON };
	static inline KeyboardKey Comma{ GLFW_KEY_COMMA };				        static inline KeyboardKey Period{ GLFW_KEY_PERIOD };
	static inline KeyboardKey Quote{ GLFW_KEY_COMMA };				        static inline KeyboardKey Slash{ GLFW_KEY_SLASH };
	static inline KeyboardKey Backslash{ GLFW_KEY_BACKSLASH };	            static inline KeyboardKey Tilde{ GLFW_KEY_GRAVE_ACCENT };
	static inline KeyboardKey Equal{ GLFW_KEY_EQUAL };					    static inline KeyboardKey Hyphen{ GLFW_KEY_APOSTROPHE };

	static inline KeyboardKey Space{ GLFW_KEY_SPACE };					    static inline KeyboardKey Enter{ GLFW_KEY_ENTER };
	static inline KeyboardKey Backspace{ GLFW_KEY_BACKSPACE };	            static inline KeyboardKey Tab{ GLFW_KEY_TAB };

	static inline KeyboardKey PageUp{ GLFW_KEY_PAGE_UP };				    static inline KeyboardKey PageDown{ GLFW_KEY_PAGE_DOWN };
	static inline KeyboardKey End{ GLFW_KEY_END };					 	    static inline KeyboardKey Home{ GLFW_KEY_HOME };

	static inline KeyboardKey Insert{ GLFW_KEY_INSERT };				    static inline KeyboardKey Delete{ GLFW_KEY_DELETE };

	static inline KeyboardKey Add{ GLFW_KEY_KP_ADD };						static inline KeyboardKey Subtract{ GLFW_KEY_KP_SUBTRACT };
	static inline KeyboardKey Multiply{ GLFW_KEY_KP_MULTIPLY };			    static inline KeyboardKey Divide{ GLFW_KEY_KP_SUBTRACT };

	static inline KeyboardKey Left{ GLFW_KEY_LEFT };						static inline KeyboardKey Right{ GLFW_KEY_RIGHT };
	static inline KeyboardKey Up{ GLFW_KEY_UP };							static inline KeyboardKey Down{ GLFW_KEY_DOWN };

	static inline KeyboardKey Numpad0{ GLFW_KEY_KP_0 };		                static inline KeyboardKey Numpad1{ GLFW_KEY_KP_1 };
	static inline KeyboardKey Numpad2{ GLFW_KEY_KP_2 };		                static inline KeyboardKey Numpad3{ GLFW_KEY_KP_3 };
	static inline KeyboardKey Numpad4{ GLFW_KEY_KP_4 };		                static inline KeyboardKey Numpad5{ GLFW_KEY_KP_5 };
	static inline KeyboardKey Numpad6{ GLFW_KEY_KP_6 };		                static inline KeyboardKey Numpad7{ GLFW_KEY_KP_7 };
	static inline KeyboardKey Numpad8{ GLFW_KEY_KP_8 };		                static inline KeyboardKey Numpad9{ GLFW_KEY_KP_9 };

	static inline KeyboardKey F1{ GLFW_KEY_F1 };							static inline KeyboardKey F2{ GLFW_KEY_F2 };
	static inline KeyboardKey F3{ GLFW_KEY_F3 };							static inline KeyboardKey F4{ GLFW_KEY_F4 };
	static inline KeyboardKey F5{ GLFW_KEY_F5 };							static inline KeyboardKey F6{ GLFW_KEY_F6 };
	static inline KeyboardKey F7{ GLFW_KEY_F7 };							static inline KeyboardKey F8{ GLFW_KEY_F8 };
	static inline KeyboardKey F9{ GLFW_KEY_F9 };							static inline KeyboardKey F10{ GLFW_KEY_F10 };
	static inline KeyboardKey F11{ GLFW_KEY_F11 };							static inline KeyboardKey F12{ GLFW_KEY_F12 };
	static inline KeyboardKey F13{ GLFW_KEY_F13 };							static inline KeyboardKey F14{ GLFW_KEY_F14 };
	static inline KeyboardKey F15{ GLFW_KEY_F15 };

	static inline KeyboardKey Pause{ GLFW_KEY_PAUSE };

private:
	static inline KeyboardKey* Keys[99] = {
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
};

}