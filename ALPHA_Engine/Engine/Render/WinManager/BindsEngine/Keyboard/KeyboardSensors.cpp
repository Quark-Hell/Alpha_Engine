#include "KeyboardSensors.h"

#include <GLFW/glfw3.h>
#include <array>

namespace Render::WindowsManager::BindsEngine {

    KeyboardData::KeyboardData(){
	    Keys = std::make_unique<std::array<KeyboardKey, 99>>(std::array<KeyboardKey, 99>{
		    KeyboardKey(GLFW_KEY_A), KeyboardKey(GLFW_KEY_B), KeyboardKey(GLFW_KEY_C), KeyboardKey(GLFW_KEY_D),
		    KeyboardKey(GLFW_KEY_E), KeyboardKey(GLFW_KEY_F), KeyboardKey(GLFW_KEY_G), KeyboardKey(GLFW_KEY_H),
		    KeyboardKey(GLFW_KEY_I), KeyboardKey(GLFW_KEY_J), KeyboardKey(GLFW_KEY_K), KeyboardKey(GLFW_KEY_L),
		    KeyboardKey(GLFW_KEY_M), KeyboardKey(GLFW_KEY_N), KeyboardKey(GLFW_KEY_O), KeyboardKey(GLFW_KEY_P),
		    KeyboardKey(GLFW_KEY_Q), KeyboardKey(GLFW_KEY_R), KeyboardKey(GLFW_KEY_S), KeyboardKey(GLFW_KEY_T),
		    KeyboardKey(GLFW_KEY_U), KeyboardKey(GLFW_KEY_V), KeyboardKey(GLFW_KEY_W), KeyboardKey(GLFW_KEY_X),
		    KeyboardKey(GLFW_KEY_Y), KeyboardKey(GLFW_KEY_Z),

		    KeyboardKey(GLFW_KEY_0), KeyboardKey(GLFW_KEY_1), KeyboardKey(GLFW_KEY_2),
	    	KeyboardKey(GLFW_KEY_3), KeyboardKey(GLFW_KEY_4), KeyboardKey(GLFW_KEY_5),
		    KeyboardKey(GLFW_KEY_6), KeyboardKey(GLFW_KEY_7), KeyboardKey(GLFW_KEY_8), KeyboardKey(GLFW_KEY_9),

		    KeyboardKey(GLFW_KEY_ESCAPE), KeyboardKey(GLFW_KEY_LEFT_CONTROL), KeyboardKey(GLFW_KEY_LEFT_SHIFT), KeyboardKey(GLFW_KEY_LEFT_ALT),
		    KeyboardKey(GLFW_KEY_RIGHT_CONTROL), KeyboardKey(GLFW_KEY_RIGHT_SHIFT), KeyboardKey(GLFW_KEY_RIGHT_ALT), KeyboardKey(GLFW_KEY_MENU),

		    KeyboardKey(GLFW_KEY_LEFT_BRACKET), KeyboardKey(GLFW_KEY_RIGHT_BRACKET),

		    KeyboardKey(GLFW_KEY_SEMICOLON), KeyboardKey(GLFW_KEY_COMMA), KeyboardKey(GLFW_KEY_PERIOD),
	    	KeyboardKey(GLFW_KEY_COMMA), KeyboardKey(GLFW_KEY_SLASH), KeyboardKey(GLFW_KEY_BACKSLASH),
		    KeyboardKey(GLFW_KEY_GRAVE_ACCENT), KeyboardKey(GLFW_KEY_EQUAL), KeyboardKey(GLFW_KEY_APOSTROPHE),

		    KeyboardKey(GLFW_KEY_SPACE), KeyboardKey(GLFW_KEY_ENTER), KeyboardKey(GLFW_KEY_BACKSPACE), KeyboardKey(GLFW_KEY_TAB),

		    KeyboardKey(GLFW_KEY_PAGE_UP), KeyboardKey(GLFW_KEY_PAGE_DOWN),

		    KeyboardKey(GLFW_KEY_END), KeyboardKey(GLFW_KEY_HOME),
	    	KeyboardKey(GLFW_KEY_INSERT), KeyboardKey(GLFW_KEY_DELETE),

		    KeyboardKey(GLFW_KEY_KP_ADD), KeyboardKey(GLFW_KEY_KP_SUBTRACT),
	    	KeyboardKey(GLFW_KEY_KP_MULTIPLY), KeyboardKey(GLFW_KEY_KP_SUBTRACT),

		    KeyboardKey(GLFW_KEY_LEFT), KeyboardKey(GLFW_KEY_RIGHT),
	    	KeyboardKey(GLFW_KEY_UP), KeyboardKey(GLFW_KEY_DOWN),

		    KeyboardKey(GLFW_KEY_KP_0), KeyboardKey(GLFW_KEY_KP_1), KeyboardKey(GLFW_KEY_KP_2), KeyboardKey(GLFW_KEY_KP_3),
		    KeyboardKey(GLFW_KEY_KP_4), KeyboardKey(GLFW_KEY_KP_5), KeyboardKey(GLFW_KEY_KP_6),
		    KeyboardKey(GLFW_KEY_KP_7), KeyboardKey(GLFW_KEY_KP_8), KeyboardKey(GLFW_KEY_KP_9),

		    KeyboardKey(GLFW_KEY_F1), KeyboardKey(GLFW_KEY_F2), KeyboardKey(GLFW_KEY_F3), KeyboardKey(GLFW_KEY_F4), KeyboardKey(GLFW_KEY_F5),
		    KeyboardKey(GLFW_KEY_F6), KeyboardKey(GLFW_KEY_F7), KeyboardKey(GLFW_KEY_F8), KeyboardKey(GLFW_KEY_F9), KeyboardKey(GLFW_KEY_F10),
		    KeyboardKey(GLFW_KEY_F11), KeyboardKey(GLFW_KEY_F12), KeyboardKey(GLFW_KEY_F13), KeyboardKey(GLFW_KEY_F14), KeyboardKey(GLFW_KEY_F15),

	    	KeyboardKey(GLFW_KEY_PAUSE)
	    });
    }
	KeyboardData* KeyboardData::GetInstance() {
	    static KeyboardData keyboard;
    	return &keyboard;
    }
}
