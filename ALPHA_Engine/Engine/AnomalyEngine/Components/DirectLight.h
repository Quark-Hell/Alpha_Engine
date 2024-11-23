#pragma once

#include "AnomalyEngine/Components/BaseLight.h"

namespace AnomalyEngine {
    class DirectLight final : public BaseLight {
        friend class DirectLightsBuffer;
    private:
        ///Do not set direction as zero vector to avoid render errors
        Core::Vector3 _direction;

    private:
        DirectLight(const Core::Vector3& direction = Core::Vector3(0, 0.7, 0.3));

    public:
        ~DirectLight() override = default;

        Core::Vector3 GetDirection();
        void SetDirection(const Core::Vector3& newDirection = Core::Vector3(0.0f, 0.7f, 0.3f));
    };
}
