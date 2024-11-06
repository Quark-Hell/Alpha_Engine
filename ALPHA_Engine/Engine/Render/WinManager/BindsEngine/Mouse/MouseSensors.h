#pragma once
#include <cstdint>
#include <Render/WinManager/BindsEngine/GeneralSensors.h>

namespace Render::WindowsManager::BindsEngine {

enum EnumMouseSensorStates : uint8_t {
    UnknownState = 1 << 0,

    MouseNotMoved = 1 << 1,
    MouseStartMoved = 1 << 2,
    MouseKeepMoved = 1 << 3,
    MouseEndMoved = 1 << 4,

    MouseEntire = 1 << 5,
    MouseLeft = 1 << 6,
};

class MouseKey
{
public:
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
