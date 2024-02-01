#pragma once

#include "Light.h"

class PointLight : public Light {
public:
	float constant = 1.0f;
	float linear = 0.7f;
	float quadratic  = 1.8f;

public:
	PointLight();
	virtual ~PointLight();

	ModulesList GetType() override;
};
