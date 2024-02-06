#include "SpotLight.h"

SpotLight::SpotLight() {

}
SpotLight::~SpotLight() {

}

ModulesList SpotLight::GetType() {
    return ModulesList::SpotLightType;
}


Vector3 SpotLight::GetDirection()
{
    return SpotLight::_direction;
}

void SpotLight::SetDirection(Vector3 newDirection)
{
    if (newDirection == Vector3(0, 0, 0)) {
        std::cout << "Warning: direction cannot be zero vector\n";
        return;
    }

    _direction = newDirection;
}