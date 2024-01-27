#include "AmbientLight.h"

AmbientLight::AmbientLight() {

}

AmbientLight::~AmbientLight() {

}

ModulesList AmbientLight::GetType() {
	return ModulesList::AmbientLightType;
}