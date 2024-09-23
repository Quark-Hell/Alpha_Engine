#pragma once

#include "Light.h"

class DirectLight : public Light {
private:
	Vector3 _direction = Vector3(0, 0.7, 0.3);

public:
	DirectLight();
	virtual ~DirectLight();

	ModulesList GetType() override;

	Vector3 GetDirection();
	void SetDirection(Vector3 newDirection);
};
