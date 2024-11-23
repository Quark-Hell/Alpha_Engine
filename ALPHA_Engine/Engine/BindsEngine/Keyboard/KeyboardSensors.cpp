#include "KeyboardSensors.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "Keyboard.h"

namespace BindsEngine {

    KeyboardSensors::KeyboardSensors() : Core::TSystemData<KeyboardKey>("KeyboardSensorsBuffer"){
		_data.reserve(99);

		_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_A));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_B));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_C));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_D));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_E));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_F));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_G));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_H));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_I));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_J));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_K));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_L));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_M));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_N));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_O));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_P));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_Q));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_R));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_S));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_T));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_U));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_V));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_W));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_X));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_Y));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_Z));

    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_0));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_1));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_2));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_3));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_4));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_5));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_6));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_7));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_8));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_9));

    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_ESCAPE));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_LEFT_CONTROL));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_LEFT_SHIFT));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_LEFT_ALT));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_RIGHT_CONTROL));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_RIGHT_SHIFT));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_RIGHT_ALT));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_MENU));

    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_LEFT_BRACKET));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_RIGHT_BRACKET));

    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_SEMICOLON));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_COMMA));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_PERIOD));

    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_COMMA)); //TODO: WTH?
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_SLASH));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_BACKSLASH));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_GRAVE_ACCENT));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_EQUAL));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_APOSTROPHE));

    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_SPACE));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_ENTER));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_BACKSPACE));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_TAB));

    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_PAGE_UP));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_PAGE_DOWN));

    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_END));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_HOME));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_INSERT));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_DELETE));

    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_KP_ADD));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_KP_SUBTRACT));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_KP_MULTIPLY));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_KP_DIVIDE));

    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_LEFT));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_RIGHT));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_UP));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_DOWN));

    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_KP_0));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_KP_1));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_KP_2));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_KP_3));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_KP_4));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_KP_5));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_KP_6));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_KP_7));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_KP_8));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_KP_9));

    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_F1));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_F2));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_F3));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_F4));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_F5));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_F6));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_F7));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_F8));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_F9));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_F10));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_F11));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_F12));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_F13));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_F14));
    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_F15));

    	_data.emplace_back(std::make_unique<KeyboardKey>(GLFW_KEY_PAUSE));
    }

	EnumKeyboardKeysStates KeyboardSensors::GetKeyState(const EnumKeyboardTable key) const {
    	for (size_t i = 0; i < 99; i++) {
    		if (_data.at(i)->KEY == key) { return _data.at(i)->KeyState; }
    	}

    	return EnumKeyboardKeysStates::KeyNotPressed;
    }
}
