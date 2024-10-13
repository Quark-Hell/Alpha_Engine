#pragma once

namespace BindsEngine {

enum EnumMouseSensorStates {
    UnknownState = 1 << 0,

    MouseNotMoved = 1 << 1,
    MouseStartMoved = 1 << 2,
    MouseKeepMoved = 1 << 3,
    MouseEndMoved = 1 << 4,

    MouseEntire = 1 << 5,
    MouseLeft = 1 << 6,
};

struct MouseKey
{
    /*
    * Definition of key by glfw3 representation
    */
    const uint8_t KEY;
    /*
    * Key state enum
    */
    EnumKeyStates KeyState;
};

}