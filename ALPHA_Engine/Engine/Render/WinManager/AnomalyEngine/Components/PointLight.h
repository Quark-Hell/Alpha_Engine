#pragma once

#include "Render/WinManager/AnomalyEngine/Components/BaseLight.h"

namespace Core {
    class Factory;
}

namespace Render::WindowsManager::AnomalyEngine {

    class PointLight final : public BaseLight {
        friend class Core::Factory;

        public:
            float Radius;
            float Constant;
            float Linear;
            float Quadratic;

        private:
          PointLight(float radius = 1.0f, float constant = 1.0f, float linear = 0.7f, float quadratic = 1.8f);

        public:
          ~PointLight() override = default;
    };

}