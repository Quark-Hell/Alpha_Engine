#include "PointLight.h"
#include "MemoryManager.h"

PointLight::PointLight() {

}
PointLight::~PointLight() {

}

ModulesList PointLight::GetType() {
    return ModulesList::PointLightType;
}