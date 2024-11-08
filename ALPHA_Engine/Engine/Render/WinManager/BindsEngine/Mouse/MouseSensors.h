#pragma once
#include <cstdint>
#include <memory>
#include "Core/Math/Vectors.h"

namespace Render::WindowsManager::BindsEngine {

    enum class EnumMouseSensorStates : uint8_t {
        Unknown,
        MouseWheelStartMoved,
        MouseWheelKeepMoved,
        MouseWheelEndMoved,

        MouseWheelMovedUp,
        MouseWheelMovedDown,

        MouseNotMoved,
        MouseStartMoved,
        MouseKeepMoved,
        MouseEndMoved
    };

    enum class EnumMouseKeysStates : uint8_t {
        KeyNotPressed,
        KeyPressed,
        KeyHold,
        KeyReleased
    };

    enum class EnumMouseTable : uint8_t {
        Left,
        Right,
        Middle,
        Extra1,
        Extra2,
        Extra3,
        Extra4,
        Extra5
    };

    class MouseKey {
    public:
        const EnumMouseTable KEY;
        EnumMouseKeysStates KeyState;

        MouseKey(const uint8_t key) : KEY(static_cast<EnumMouseTable>(key)) {}
        ~MouseKey() = default;
    };

    class MouseData {
        friend class Mouse;

    private:
        std::shared_ptr<std::array<MouseKey, 8>> Keys;

        Core::Vector2 _previousMousePos;
        Core::Vector2 _currentMousePos;
        Core::Vector2 _mouseDelta;

        EnumMouseSensorStates _mouseSensorState;
    private:
        MouseData();

    public:
        static MouseData *GetInstance();
        ~MouseData() = default;
    };
}