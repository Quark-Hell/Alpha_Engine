#include "Keyboard.h"
#include "BaseConfig.h"
#include "GLFW/glfw3.h"

namespace Render::WindowsManager::BindsEngine {
    Keyboard::Keyboard() = default;
    Keyboard::~Keyboard() = default;

    EnumKeyStates Keyboard::GetKeyState(const uint16_t key) {
        const auto keyboard = KeyboardData::GetInstance();

        for (size_t i = 0; i < 99; i++) {
            if (static_cast<uint16_t>(keyboard->Keys->at(i).KEY) == key) { return keyboard->Keys->at(i).KeyState; }
        }
        return EnumKeyStates::Unknown;
    }

    void Keyboard::UpdateKeysState() {
        const auto keyboard = KeyboardData::GetInstance();
        const auto win = glfwGetCurrentContext();

        for (auto &key: *keyboard->Keys) {
            if (glfwGetKey(win, static_cast<uint16_t>(key.KEY))) {
                if (key.KeyState & KeyNotPressed) {
                    key.KeyState = KeyPressed;
                    //std::cout << "Pressed" << std::endl;
                } else if (key.KeyState & KeyPressed) {
                    key.KeyState = KeyHold;
                    //std::cout << "Hold" << std::endl;
                }
            } else {
                if (key.KeyState & KeyHold || key.KeyState & KeyPressed) {
                    key.KeyState = KeyReleased;
                    //std::cout << "Released" << std::endl;
                    continue;
                }
                key.KeyState = KeyNotPressed;
            }
        }
    }
}
