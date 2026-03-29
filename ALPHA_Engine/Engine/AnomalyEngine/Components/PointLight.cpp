#include "PointLight.h"

namespace AnomalyEngine {
    PointLight::PointLight(const float radius, const float constant, const float linear, const float quadratic){
        Radius = radius;
        Constant = constant;
        Linear = linear;
        Quadratic = quadratic;
    }
}