#include "PointLight.h"

namespace Render::WindowsManager::AnomalyEngine {
    PointLight::PointLight(float radius, float constant, float linear, float quadratic){
        Radius = radius;
        Constant = constant;
        Linear = linear;
        Quadratic = quadratic;
    }
}