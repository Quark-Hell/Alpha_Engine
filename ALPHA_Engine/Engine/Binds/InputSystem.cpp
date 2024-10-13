#include "InputSystem.h"

namespace BindsEngine {

InputSystem::InputSystem() {
    InputSystem::Window = Window;
}
InputSystem::~InputSystem() = default;

void InputSystem::IO_Events() {
    if (!InputSystem::Window) { return; }

    InputSystem::_mouseClass->UpdateMouseState(*InputSystem::Window);
    InputSystem::_keyboardClass->UpdateKeysState(*InputSystem::Window);

    //if (!InputSystem::Screen->isOpen()) { return; }
    //if (InputSystem::Screen->pollEvent(InputSystem::_event)) { }


    //All values
    for (size_t i = 0; i < InputSystem::_bindsBuff.size(); i++)
    {
        if (InputSystem::_bindsBuff[i].Active == false) { continue; }
        bool mark = true;

        //Keyboard statement check
        for (size_t j = 0; j < InputSystem::_bindsBuff[i]._keyboardKeys.size(); j++)
        {
            EnumKeyStates state = InputSystem::_keyboardClass->GetKeyState(InputSystem::_bindsBuff[i]._keyboardKeys[j]);
            if (! (InputSystem::_bindsBuff[i]._keyboardKeysState[j] & state)) { mark = false; break; }
        }

        //Mouse button statement check
        for (size_t j = 0; j < InputSystem::_bindsBuff[i]._mouseKeys.size(); j++)
        {
            int IdCurrentKey = InputSystem::_bindsBuff[i]._mouseKeys[j];
            if (!(InputSystem::_bindsBuff[i]._mouseKeysState[j] & InputSystem::_mouseClass->Buttons[IdCurrentKey]->KeyState)) { mark = false; break; }
        }

        //Check mouse sensor statement
        if(InputSystem::_bindsBuff[i]._mouseSensorState & UnknownState) {}
        else if (!(InputSystem::_bindsBuff[i]._mouseSensorState & InputSystem::_mouseClass->MoveSensorState)) { mark = false; }

        if (mark) { InputSystem::_bindsBuff[i].InvokeOperations(); }
    }
}

void InputSystem::ClearBindsBuffer() {
    InputSystem::_bindsBuff.clear();
}
void InputSystem::InsertBindWithClear(Bind bind) {
    ClearBindsBuffer();
    InputSystem::_bindsBuff.push_back(bind);
}
void InputSystem::InsertBind(Bind bind) {
    InputSystem::_bindsBuff.push_back(bind);
}

Mouse* InputSystem::GetMouseClass() {
    return InputSystem::_mouseClass;
}

}