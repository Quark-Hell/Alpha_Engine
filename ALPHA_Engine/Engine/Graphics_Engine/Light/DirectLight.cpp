#include "DirectLight.h"

DirectLight::DirectLight() {

}
DirectLight::~DirectLight() {

}

ModulesList DirectLight::GetType() {
    return ModulesList::DirectLightType;
}


Vector3 DirectLight::GetDirection()
{
    return DirectLight::_direction;
}

void DirectLight::SetDirection(Vector3 newDirection)
{
    if (newDirection == Vector3(0, 0, 0)) {
        std::cout << "Warning: direction cannot be zero vector\n";
        return;
    }
        
    _direction = Vector3::GetNormalize(newDirection);
}
