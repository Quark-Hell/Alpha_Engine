#include <GLFW/glfw3.h>
#include "KeyboardSensors.h"

#include <array>

namespace Render::WindowsManager::BindsEngine {

    KeyboardData::KeyboardData():
	A(GLFW_KEY_A), B(GLFW_KEY_B), C(GLFW_KEY_C), D(GLFW_KEY_D), E(GLFW_KEY_E), F(GLFW_KEY_F), G(GLFW_KEY_G), H(GLFW_KEY_H), I(GLFW_KEY_I),
	J(GLFW_KEY_J), K(GLFW_KEY_K), L(GLFW_KEY_L), M(GLFW_KEY_M), N(GLFW_KEY_N), O(GLFW_KEY_O), P(GLFW_KEY_P), Q(GLFW_KEY_Q), R(GLFW_KEY_R),
	S(GLFW_KEY_S), T(GLFW_KEY_T), U(GLFW_KEY_U), V(GLFW_KEY_V), W(GLFW_KEY_W), X(GLFW_KEY_X), Y(GLFW_KEY_Y), Z(GLFW_KEY_Z),

    Num0(GLFW_KEY_0), Num1(GLFW_KEY_1), Num2(GLFW_KEY_2), Num3(GLFW_KEY_3), Num4(GLFW_KEY_4),
    Num5(GLFW_KEY_5), Num6(GLFW_KEY_6), Num7(GLFW_KEY_7), Num8(GLFW_KEY_8), Num9(GLFW_KEY_9),

    Escape(GLFW_KEY_ESCAPE), LControl(GLFW_KEY_LEFT_CONTROL), LShift(GLFW_KEY_LEFT_SHIFT), LAlt(GLFW_KEY_LEFT_ALT),
    RControl(GLFW_KEY_RIGHT_CONTROL), RShift(GLFW_KEY_RIGHT_SHIFT), RAlt(GLFW_KEY_RIGHT_ALT), Menu(GLFW_KEY_MENU),

    LBracket(GLFW_KEY_LEFT_BRACKET), RBracket(GLFW_KEY_RIGHT_BRACKET), Semicolon(GLFW_KEY_SEMICOLON), Comma(GLFW_KEY_COMMA),
	Period(GLFW_KEY_PERIOD), Quote(GLFW_KEY_COMMA), Slash(GLFW_KEY_SLASH), Backslash(GLFW_KEY_BACKSLASH),
    Tilde(GLFW_KEY_GRAVE_ACCENT), Equal(GLFW_KEY_EQUAL), Hyphen(GLFW_KEY_APOSTROPHE), Space(GLFW_KEY_SPACE),

	Enter(GLFW_KEY_ENTER), Backspace(GLFW_KEY_BACKSPACE), Tab(GLFW_KEY_TAB),

    PageUp(GLFW_KEY_PAGE_UP), PageDown(GLFW_KEY_PAGE_DOWN), End(GLFW_KEY_END), Home(GLFW_KEY_HOME),

	Insert(GLFW_KEY_INSERT), Delete(GLFW_KEY_DELETE), Add(GLFW_KEY_KP_ADD),
    Subtract(GLFW_KEY_KP_SUBTRACT), Multiply(GLFW_KEY_KP_MULTIPLY), Divide(GLFW_KEY_KP_SUBTRACT),

    Left(GLFW_KEY_LEFT), Right(GLFW_KEY_RIGHT), Up(GLFW_KEY_UP), Down(GLFW_KEY_DOWN),

    Numpad0(GLFW_KEY_KP_0), Numpad1(GLFW_KEY_KP_1), Numpad2(GLFW_KEY_KP_2), Numpad3(GLFW_KEY_KP_3), Numpad4(GLFW_KEY_KP_4),
    Numpad5(GLFW_KEY_KP_5), Numpad6(GLFW_KEY_KP_6), Numpad7(GLFW_KEY_KP_7), Numpad8(GLFW_KEY_KP_8), Numpad9(GLFW_KEY_KP_9),

	F1(GLFW_KEY_F1), F2(GLFW_KEY_F2), F3(GLFW_KEY_F3), F4(GLFW_KEY_F4), F5(GLFW_KEY_F5),
    F6(GLFW_KEY_F6), F7(GLFW_KEY_F7), F8(GLFW_KEY_F8), F9(GLFW_KEY_F9), F10(GLFW_KEY_F10),
    F11(GLFW_KEY_F11), F12(GLFW_KEY_F12), F13(GLFW_KEY_F13), F14(GLFW_KEY_F14), F15(GLFW_KEY_F15),
	Pause(GLFW_KEY_PAUSE) {

	    Keys = std::make_unique<std::array<KeyboardKey *, 99> >(std::array<KeyboardKey *, 99>{
		    &A, &B, &C, &D,
		    &E, &F, &G, &H,
		    &I, &J, &K, &L,
		    &M, &N, &O, &P,
		    &Q, &R, &S, &T,
		    &U, &V, &W, &X,
		    &Y, &Z,

		    &Num0, &Num1,
		    &Num2, &Num3, &Num4, &Num5,
		    &Num6, &Num7, &Num8, &Num9,

		    &Escape, &LControl, &LShift, &LAlt,
		    &RControl, &RShift, &RAlt, &Menu,

		    &LBracket, &RBracket,

		    &Semicolon, &Comma, &Period, &Quote, &Slash, &Backslash,
		    &Tilde, &Equal, &Hyphen,

		    &Space, &Enter, &Backspace, &Tab,

		    &PageUp, &PageDown,

		    &End, &Home, &Insert, &Delete,

		    &Add, &Subtract, &Multiply, &Divide,

		    &Left, &Right, &Up, &Down,

		    &Numpad0, &Numpad1, &Numpad2, &Numpad3,
		    &Numpad4, &Numpad5, &Numpad6,
		    &Numpad7, &Numpad8, &Numpad9,

		    &F1, &F2, &F3, &F4, &F5,
		    &F6, &F7, &F8, &F9, &F10,
		    &F11, &F12, &F13, &F14, &F15,

		    &Pause
	    });
    }
	KeyboardData* KeyboardData::GetInstance() {
	    static KeyboardData keyboard;
    	return &keyboard;
    }
}
