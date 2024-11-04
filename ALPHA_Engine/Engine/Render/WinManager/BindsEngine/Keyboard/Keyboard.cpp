#include "Keyboard.h"
#include "BaseConfig.h"
#include "GLFW/glfw3.h"

namespace Render::WindowsManager::BindsEngine {
Keyboard::Keyboard() = default;
Keyboard::~Keyboard() = default;

EnumKeyStates Keyboard::GetKeyState(const uint16_t key) {
  for (size_t i = 0; i < 99; i++)
  {
    if (KeyboardData::Keys[i]->KEY == key) { return KeyboardData::Keys[i]->KeyState; }
  }
  return EnumKeyStates::Unknown;
}
void Keyboard::UpdateKeysState(GLFWwindow& window) {
  for (size_t i = 0; i < 99; i++)
  {
    if (glfwGetKey(&window, KeyboardData::Keys[i]->KEY)) {
      if (KeyboardData::Keys[i]->KeyState & EnumKeyStates::KeyNotPressed) {
        KeyboardData::Keys[i]->KeyState = KeyPressed;
        std::cout << "Pressed" << std::endl;
      }
      else if (KeyboardData::Keys[i]->KeyState & EnumKeyStates::KeyPressed) {
        KeyboardData::Keys[i]->KeyState = KeyHold;
        std::cout << "Hold" << std::endl;
      }
    }
    else
    {
      if (KeyboardData::Keys[i]->KeyState & EnumKeyStates::KeyHold || KeyboardData::Keys[i]->KeyState & EnumKeyStates::KeyPressed) {
        KeyboardData::Keys[i]->KeyState = KeyReleased;
        std::cout << "Released" << std::endl;
        continue;
      }
      KeyboardData::Keys[i]->KeyState = KeyNotPressed;
    }
  }
}

}
