#pragma once

#include "Basical_Type.h"
#include "Light.h"

class AmbientLight : public Light {
public:
	AmbientLight();
	virtual ~AmbientLight();

	ModulesList GetType() override;
};