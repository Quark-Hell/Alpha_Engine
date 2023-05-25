#pragma once
#include "Module.h"

class Camera : public Module{
public:
	const ModulesList _type = ModulesList::CameraType;

private:
	float Fov = 90;
	float Aspect = 1;
	float ZNear = 1;
	float ZFar = 300;
	Vector3 DirectionOfView;

public:
	void SetCameraInfo(float Fov, float Aspect, float ZNear, float ZFar);
	void GetCameraInfo(float* Fov, float* Aspect, float* ZNear, float* ZFar);

	ModulesList GetType() override;

	float GetFov();
	float GetAspect();
	float GetZNear();
	float GetZFar();

	Vector3 GetDirectionOfView();

	Camera();
	~Camera();
};