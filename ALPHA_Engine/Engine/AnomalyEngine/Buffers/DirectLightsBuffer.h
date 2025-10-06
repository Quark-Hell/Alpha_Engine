#pragma once

#include "AnomalyEngine/Components/DirectLight.h"
#include "Core/ECS/TSystemData.h"

namespace AnomalyEngine {
    class DirectLightsBuffer final : public Core::TSystemData<DirectLight> {
        friend class RenderEngine;

        public:
        DirectLightsBuffer(size_t initialBufferSize = 0);
        ~DirectLightsBuffer() override = default;

        DirectLight& CreateDirectLight(const glm::vec3& direction = glm::vec3(0, 0.7, 0.3));
    };
}


