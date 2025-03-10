#pragma once

#include "AnomalyEngine/Components/BaseLight.h"

namespace AnomalyEngine {
    class DirectLight final : public BaseLight {
        friend class DirectLightsBuffer;
    private:
        ///Do not set direction as zero vector to avoid render errors
        glm::vec3 _direction = glm::vec3(0, 0.7, 0.3);

    private:
        DirectLight(const glm::vec3& direction);

    public:
        ~DirectLight() override = default;

        glm::vec3 GetDirection();
        void SetDirection(const glm::vec3& newDirection = glm::vec3(0.0f, 0.7f, 0.3f));
    };
}
