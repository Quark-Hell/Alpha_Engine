#pragma once

#include "Light.h"

class SpotLight : public Light {
public:
	float CutOff;
	float OuterCutOff;

public:
	SpotLight();
	virtual ~SpotLight();

	ModulesList GetType() override;

	Vector3 GetDirection();
};
