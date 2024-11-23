#pragma once

#include "AnomalyEngine/Components/PointLight.h"
#include "Core/ECS/TSystemData.h"

namespace AnomalyEngine {
    class PointLightsBuffer final : public Core::TSystemData<PointLight> {
        public:
        PointLightsBuffer();
        ~PointLightsBuffer() override = default;

        PointLight* CreatePointLight(float radius = 1.0f, float constant = 1.0f, float linear = 0.7f, float quadratic = 1.8f);
    };
}

