#include "DirectLight.h"

#include "Core/Logger/Logger.h"

namespace AnomalyEngine {
    DirectLight::DirectLight(const glm::vec3& direction) {
        SetDirection(direction);
    }

    glm::vec3 DirectLight::GetDirection() {
        return _direction;
    }

    void DirectLight::SetDirection(const glm::vec3& newDirection) {
        if (newDirection == glm::vec3(0,0,0)) {
            Core::Logger::LogError("Direction cannot be zero vector: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            return;
        }

        _direction = glm::normalize(newDirection);
    }
}