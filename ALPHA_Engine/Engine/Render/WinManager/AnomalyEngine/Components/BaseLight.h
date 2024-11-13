#pragma once

#include <Core/Math/Vectors.h>
#include "Core/Components/Component.h"

namespace Render::AnomalyEngine::Components {
    class BaseLight : public Core::Component {
        public:
            Core::Vector3 color{1,1,1};
            float intensity = 1.0f;

        protected:
            BaseLight() = default;
            ~BaseLight() override = default;
    };
}
