#include "InputSystem.h"

#include <Render/WinManager/BindsEngine/Keyboard/Keyboard.h>
#include <Render/WinManager/BindsEngine/Mouse/Mouse.h>

#include <Render/WinManager/BindsEngine/Binds.h>

namespace Render::WindowsManager::BindsEngine {

void InputSystem::IO_Events(GLFWwindow& window) {
    InputSystem::_mouseClass->UpdateMouseState(window);
    InputSystem::_keyboardClass->UpdateKeysState(window);

    //if (!InputSystem::Screen->isOpen()) { return; }
    //if (InputSystem::Screen->pollEvent(InputSystem::_event)) { }


    //All values
    for (auto& bind : InputSystem::_bindsBuff) {
        if (bind.Active == false) { continue; }
        bool mark = true;

        //Keyboard statement check
        for (size_t j = 0; j < bind._keyboardKeys.size(); j++)
        {
            const EnumKeyStates state = InputSystem::_keyboardClass->GetKeyState(bind._keyboardKeys[j]);
            if (! (bind._keyboardKeysState[j] & state)) { mark = false; break; }
        }

        //Mouse button statement check
        for (size_t j = 0; j < bind._mouseKeys.size(); j++)
        {
            const int idCurrentKey = bind._mouseKeys[j];
            if (!(bind._mouseKeysState[j] & InputSystem::_mouseClass->Buttons[idCurrentKey]->KeyState)) { mark = false; break; }
        }

        //Check mouse sensor statement
        if(bind._mouseSensorState & UnknownState) {}
        else if (!(bind._mouseSensorState & InputSystem::_mouseClass->MoveSensorState)) { mark = false; }

        if (mark) { bind.InvokeOperations(); }
    }
}

void InputSystem::ClearBindsBuffer() {
    InputSystem::_bindsBuff.clear();
}
void InputSystem::InsertBind(const Bind& bind) {
    InputSystem::_bindsBuff.push_back(bind);
}

}