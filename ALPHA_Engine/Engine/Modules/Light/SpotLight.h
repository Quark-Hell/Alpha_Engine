#pragma once

#include "Light.h"

class SpotLight : public Light {
public:
	float CutOff;
	float OuterCutOff;

private:
	Vector3 _direction;

public:
	SpotLight();
	virtual ~SpotLight();

	ModulesList GetType() override;

	Vector3 GetDirection();
	void SetDirection(Vector3 newDirection);
};
