#pragma once
class Vector3;

#include "Core/Modules/Module.h"
#include "Core/Modules/Transform.h"

#include "glm.hpp"


enum ProjectionMode {
	Perspective = 0,
	Orthographic = 1,
};

class Camera : public Module {
private:
	Transform _transform;

	float Fov = 90;
	float Aspect = 1;
	float ZNear = 0.1f;
	float ZFar = 300;

	//TODO: Add function for change mode
	ProjectionMode _projectionMode = ProjectionMode::Perspective;

	glm::mat4x4 _projectionMatrix = glm::mat4x4(1.0f);

public:
	Camera();
	~Camera();

	void SetCameraInfo(float Fov, float Aspect, float ZNear, float ZFar);
	void GetCameraInfo(float* Fov, float* Aspect, float* ZNear, float* ZFar);

	ModulesList GetType() override;

	Object* GetParentObject() override;
	void SetParentObject(const Object& parent) override;

	float GetFov();
	float GetAspect();
	float GetZNear();
	float GetZFar();

	glm::mat4x4 GetProjectionMatrix();
	glm::mat4x4 GetTransformMatrix();

	void UpdateProjectionMatrix();
	void UpdateViewMatrix();
};