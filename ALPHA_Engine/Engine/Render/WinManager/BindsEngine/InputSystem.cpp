#include "InputSystem.h"

#include <GLFW/glfw3.h>
#include <Render/WinManager/Window.h>
#include <Render/WinManager/WindowsBuffer.h>

#include <Render/WinManager/BindsEngine/Keyboard/Keyboard.h>
#include <Render/WinManager/BindsEngine/Mouse/Mouse.h>
#include <Render/WinManager/BindsEngine/Binds.h>
#include "BindsBuffer.h"

#include "Keyboard/KeyboardSensors.h"
#include "Mouse/MouseSensors.h"

namespace Render::WindowsManager::BindsEngine {

    InputSystem::InputSystem() : System({"BindsBuffer", "WindowsBuffer"}, 200) {
        _mouseClass = std::unique_ptr<Mouse>(new Mouse());
        _keyboardClass = std::unique_ptr<Keyboard>(new Keyboard());
    }

    InputSystem* InputSystem::GetInstance() {
        static InputSystem instance;
        return &instance;
    }

    void InputSystem::EntryPoint(std::vector<Core::SystemData*>& data) {
        auto* bindsBuffer = reinterpret_cast<BindsBuffer*>(data[0]);
        auto* windowsBuffer = reinterpret_cast<WindowsBuffer*>(data[1]);

        //Seek active window
        const Window* activeWindow = nullptr;
        for (size_t i = 0; i < windowsBuffer->GetAllData().size(); i++) {
            auto& component = windowsBuffer->GetData(i);

            if (glfwGetWindowAttrib(component._window, GLFW_FOCUSED)) {
                activeWindow = &component;
            }
        }
        if (activeWindow == nullptr) {
            return;
        }

        glfwMakeContextCurrent(activeWindow->_window);


        InputSystem::_mouseClass->UpdateMouseState();
        InputSystem::_keyboardClass->UpdateKeysState();

        //All values
        for (size_t i = 0; i < bindsBuffer->GetAllData().size(); i++) {

            auto& component = bindsBuffer->GetData(i);

            if (component.IsActive == false) { continue; }
            bool mark = true;

            //Keyboard statement check
            for (size_t j = 0; j < component._keyboardKeys.size(); j++)
            {
                const EnumKeyboardKeysStates state = InputSystem::_keyboardClass->GetKeyState(component._keyboardKeys[j]);

                if (component._keyboardKeysState[j] != state) { mark = false; break; }
            }

            //Mouse button statement check
            for (size_t j = 0; j < component._mouseKeys.size(); j++)
            {
                EnumMouseKeysStates state = InputSystem::_mouseClass->GetKeyState(component._mouseKeys[j]);

                if (component._mouseKeysState[j] != state) { mark = false; break; }
            }

            const EnumMouseSensorStates state = InputSystem::_mouseClass->GetSensorState();

            //Check mouse sensor statement
            for (const auto& it : component._mouseSensorState) {
                if (it == EnumMouseSensorStates::Unknown && it != state) {
                    mark = false;
                    break;
                }
                else {
                    mark = true;
                    break;
                }
            }

            Logger::Logger::LogInfo(mark);
            if (mark) { component.InvokeOperations(activeWindow); }
        }
    }

    Mouse* InputSystem::GetMouse() const {
        return _mouseClass.get();
    }

    Keyboard* InputSystem::GetKeyboard() const {
        return _keyboardClass.get();
    }
}
