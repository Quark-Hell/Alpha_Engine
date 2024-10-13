#pragma once

namespace BindsEngine {

enum EnumKeyStates {
    Unknown = -1,

    KeyNotPressed = 1 << 0,
    KeyPressed = 1 << 1,
    KeyHold = 1 << 2,
    KeyReleased = 1 << 3,

    MouseWheelStartMoved = 1 << 4,
    MouseWheelKeepMoved = 1 << 5,
    MouseWheelEndMoved = 1 << 6,

    MouseWheelMovedUp = 1 << 7,
    MouseWheelMovedDown = 1 << 8
};

}