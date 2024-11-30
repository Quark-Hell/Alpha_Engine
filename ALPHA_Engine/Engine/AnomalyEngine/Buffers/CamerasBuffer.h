#pragma once

#include "AnomalyEngine/Components/Camera.h"
#include "Core/ECS/TSystemData.h"

namespace AnomalyEngine {
    class CamerasBuffer final : public Core::TSystemData<Camera> {
        friend class RenderEngine;

        public:
        CamerasBuffer();
        ~CamerasBuffer() override = default;

        Camera& CreateCamera(size_t width = 100, size_t height = 100, float fov = 60, float aspect = 1.3333333, float zNear = 0.01, float zFar = 10000);
    };
}

