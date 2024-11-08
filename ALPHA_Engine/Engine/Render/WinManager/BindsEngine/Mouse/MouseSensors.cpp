#include "MouseSensors.h"

#include <GLFW/glfw3.h>
#include <array>

namespace Render::WindowsManager::BindsEngine {
    MouseData::MouseData() {
      Keys = std::make_unique<std::array<MouseKey, 8>>(std::array<MouseKey, 8>{
          MouseKey(GLFW_MOUSE_BUTTON_1), MouseKey(GLFW_MOUSE_BUTTON_2),
          MouseKey(GLFW_MOUSE_BUTTON_3), MouseKey(GLFW_MOUSE_BUTTON_4),
          MouseKey(GLFW_MOUSE_BUTTON_5), MouseKey(GLFW_MOUSE_BUTTON_6),
          MouseKey(GLFW_MOUSE_BUTTON_7), MouseKey(GLFW_MOUSE_BUTTON_8)
      });
    }

    MouseData* MouseData::GetInstance() {
        static MouseData mouse;
        return &mouse;
    }
}