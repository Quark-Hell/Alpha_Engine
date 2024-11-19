#pragma once

#include <Core/Math/Vectors.h>
#include "Core/Components/Component.h"

namespace Render::WindowsManager::AnomalyEngine {
    class BaseLight : public Core::Component {
        public:
            Core::Vector3 Color{1,1,1};
            float Intensity = 1.0f;

        protected:
            BaseLight() = default;
            ~BaseLight() override = default;
    };
}
