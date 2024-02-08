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
    return Vector3::GetNormalize(-SpotLight::_lookingPoint);
}
