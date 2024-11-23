#include "DirectLight.h"

#include "Core/Logger/Logger.h"

namespace Render::WindowsManager::AnomalyEngine {
    DirectLight::DirectLight(const Core::Vector3& direction) {
        SetDirection(direction);
    }

    Core::Vector3 DirectLight::GetDirection() {
        return _direction;
    }

    void DirectLight::SetDirection(const Core::Vector3& newDirection) {
        if (newDirection == Core::Vector3(0,0,0)) {
            Core::Logger::LogError("Direction cannot be zero vector: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            return;
        }

        _direction = Core::Vector3::GetNormalize(newDirection);
    }
}