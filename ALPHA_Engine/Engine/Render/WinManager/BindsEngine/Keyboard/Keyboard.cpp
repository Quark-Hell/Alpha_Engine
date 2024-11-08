#include "Keyboard.h"

#include <array>
#include "GLFW/glfw3.h"

#include "iostream"

namespace Render::WindowsManager::BindsEngine {

    EnumKeyboardKeysStates Keyboard::GetKeyState(const EnumKeyboardTable key) {
        const auto keyboard = KeyboardData::GetInstance();

        for (size_t i = 0; i < 99; i++) {
            if (keyboard->Keys->at(i).KEY == key) { return keyboard->Keys->at(i).KeyState; }
        }

        return EnumKeyboardKeysStates::KeyNotPressed;
    }

    void Keyboard::UpdateKeysState() {
        const auto keyboard = KeyboardData::GetInstance();
        const auto win = glfwGetCurrentContext();

        for (auto &key: *keyboard->Keys) {
            if (glfwGetKey(win, static_cast<uint16_t>(key.KEY))) {
                if (key.KeyState == EnumKeyboardKeysStates::KeyNotPressed) {
                    key.KeyState = EnumKeyboardKeysStates::KeyPressed;
                    //std::cout << "Pressed" << std::endl;
                } else if (key.KeyState == EnumKeyboardKeysStates::KeyPressed) {
                    key.KeyState = EnumKeyboardKeysStates::KeyHold;
                    //std::cout << "Hold" << std::endl;
                }
            } else {
                if (key.KeyState == EnumKeyboardKeysStates::KeyHold || key.KeyState == EnumKeyboardKeysStates::KeyPressed) {
                    key.KeyState = EnumKeyboardKeysStates::KeyReleased;
                    //std::cout << "Released" << std::endl;
                    continue;
                }
                key.KeyState = EnumKeyboardKeysStates::KeyNotPressed;
            }
        }
    }
}
