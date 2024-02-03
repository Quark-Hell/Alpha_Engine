#pragma once

#include "Light.h"

//TODO: Add interpolation to linear and quadric values

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
