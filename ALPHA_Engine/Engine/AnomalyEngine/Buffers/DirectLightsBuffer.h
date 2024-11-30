#pragma once

#include "AnomalyEngine/Components/DirectLight.h"
#include "Core/ECS/TSystemData.h"

namespace AnomalyEngine {
    class DirectLightsBuffer final : public Core::TSystemData<DirectLight> {
        friend class RenderEngine;

        public:
        DirectLightsBuffer();
        ~DirectLightsBuffer() override = default;

        DirectLight& CreateDirectLight(const Core::Vector3& direction = Core::Vector3(0, 0.7, 0.3));
    };
}


