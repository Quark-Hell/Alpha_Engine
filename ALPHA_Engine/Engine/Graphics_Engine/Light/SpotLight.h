#pragma once

#include "Light.h"

class SpotLight : public Light {
public:
	float CutOff;
	float OuterCutOff;

public:
	SpotLight();
	~SpotLight();

	ModulesList GetType() override;
};
