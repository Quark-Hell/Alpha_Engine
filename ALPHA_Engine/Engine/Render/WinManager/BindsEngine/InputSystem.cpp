#include "InputSystem.h"

#include <GLFW/glfw3.h>
#include <Render/WinManager/Window.h>
#include <Render/WinManager/BindsEngine/Keyboard/Keyboard.h>
#include <Render/WinManager/BindsEngine/Mouse/Mouse.h>

#include <Render/WinManager/BindsEngine/Binds.h>

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
        bindsBuffer = buffer;
    }

    void InputSystem::IO_Events(const Render::WindowsManager::Window* window) const {
        if (bindsBuffer == nullptr) { return; }

        InputSystem::_mouseClass->UpdateMouseState();
        InputSystem::_keyboardClass->UpdateKeysState();

        //All values
        for (const auto& bind : *bindsBuffer) {
            if (bind->IsActive == false) { continue; }
            bool mark = true;

            //Keyboard statement check
            for (size_t j = 0; j < bind->_keyboardKeys.size(); j++)
            {
                const EnumKeyStates state = InputSystem::_keyboardClass->GetKeyState(static_cast<uint16_t>(bind->_keyboardKeys[j]));
                if (! (bind->_keyboardKeysState[j] & state)) { mark = false; break; }
            }

            //Mouse button statement check
            for (size_t j = 0; j < bind->_mouseKeys.size(); j++)
            {
                const int idCurrentKey = bind->_mouseKeys[j];
                if (!(bind->_mouseKeysState[j] & InputSystem::_mouseClass->Buttons[idCurrentKey]->KeyState)) { mark = false; break; }
            }

            //Check mouse sensor statement
            if(bind->_mouseSensorState & UnknownState) {}
            else if (!(bind->_mouseSensorState & InputSystem::_mouseClass->MoveSensorState)) { mark = false; }

            if (mark) { bind->InvokeOperations(window); }
        }
    }

    Mouse* InputSystem::GetMouse() {
        return _mouseClass.get();
    }

    Keyboard* InputSystem::GetKeyboard() {
        return _keyboardClass.get();
    }
}