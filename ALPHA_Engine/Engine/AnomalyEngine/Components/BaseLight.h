#pragma once

#include <Core/Math/Vectors.h>
#include "Core/Components/Component.h"

namespace AnomalyEngine {
    class BaseLight : public Core::Component {
        public:
            glm::vec3 Color{1,1,1};
            float Intensity = 1.0f;

        protected:
            BaseLight() = default;
            ~BaseLight() override = default;
    };
}
