#include "InputSystem.h"

#include <Render/WinManager/Window.h>
#include <Render/WinManager/BindsEngine/Keyboard/Keyboard.h>
#include <Render/WinManager/BindsEngine/Mouse/Mouse.h>

#include <Render/WinManager/BindsEngine/Binds.h>

#include "Keyboard/KeyboardSensors.h"
#include "Mouse/MouseSensors.h"

namespace Render::WindowsManager::BindsEngine {

    InputSystem::InputSystem() {
        _mouseClass = std::unique_ptr<Mouse>(new Mouse());
        _keyboardClass = std::unique_ptr<Keyboard>(new Keyboard());
    }

    InputSystem* InputSystem::GetInstance() {
        static InputSystem instance;
        return &instance;
    }

    void InputSystem::LoadBindsBuffer(std::list<std::unique_ptr<Render::WindowsManager::BindsEngine::Bind>>* buffer) {
        _bindsBuffer = buffer;
    }

    void InputSystem::IO_Events(const Render::WindowsManager::Window* window) const {
        if (_bindsBuffer == nullptr) { return; }

        InputSystem::_mouseClass->UpdateMouseState();
        InputSystem::_keyboardClass->UpdateKeysState();

        //All values
        for (const auto& bind : *_bindsBuffer) {
            if (bind->IsActive == false) { continue; }
            bool mark = true;

            //Keyboard statement check
            for (size_t j = 0; j < bind->_keyboardKeys.size(); j++)
            {
                const EnumKeyboardKeysStates state = InputSystem::_keyboardClass->GetKeyState(bind->_keyboardKeys[j]);

                if (bind->_keyboardKeysState[j] != state) { mark = false; break; }
            }

            //Mouse button statement check
            for (size_t j = 0; j < bind->_mouseKeys.size(); j++)
            {
                EnumMouseKeysStates state = InputSystem::_mouseClass->GetKeyState(bind->_mouseKeys[j]);

                if (bind->_mouseKeysState[j] != state) { mark = false; break; }
            }

            const EnumMouseSensorStates state = InputSystem::_mouseClass->GetSensorState();

            //Check mouse sensor statement
            for (const auto& it : bind->_mouseSensorState) {
                if (it == EnumMouseSensorStates::Unknown && it != state) {
                    mark = false;
                    break;
                }
                else {
                    mark = true;
                    break;
                }
            }

            if (mark) { bind->InvokeOperations(window); }
        }
    }

    Mouse* InputSystem::GetMouse() const {
        return _mouseClass.get();
    }

    Keyboard* InputSystem::GetKeyboard() const {
        return _keyboardClass.get();
    }
}
