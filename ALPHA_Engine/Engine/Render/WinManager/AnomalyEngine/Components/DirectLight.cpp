#include "DirectLight.h"

namespace Render::AnomalyEngine::Components {
    DirectLight::DirectLight(const Core::Vector3& direction) {
        SetDirection(direction);
    }

    Core::Vector3 DirectLight::GetDirection() {
        return _direction;
    }

    void DirectLight::SetDirection(const Core::Vector3& newDirection) {
        if (newDirection == Core::Vector3(0,0,0)) {
            std::cout << "Error: direction cannot be zero vector" << std::endl;
            return;
        }

        _direction = Core::Vector3::GetNormalize(newDirection);
    }
}