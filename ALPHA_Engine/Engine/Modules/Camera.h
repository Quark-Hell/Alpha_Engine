#pragma once
#include "Module.h"

#include "Modules/MovableModule.h"

#define GLEW_STATIC
#include <GL/glew.h>

//OpenGL
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#include <gl/gl.h>
#include <gl/glu.h>

enum ProjectionMode {
	Perspective = 0,
	Orthographic = 1,
};

class Camera : public virtual MovableModule {
private:
	float Fov = 90;
	float Aspect = 1;
	float ZNear = 1;
	float ZFar = 300;
	Vector3 DirectionOfView;

	//TODO: Add function for change mode
	ProjectionMode _projectionMode = ProjectionMode::Perspective;

	glm::mat4x4 _projectionMatrix = glm::mat4x4(1.0f);

public:
	void SetCameraInfo(float Fov, float Aspect, float ZNear, float ZFar);
	void GetCameraInfo(float* Fov, float* Aspect, float* ZNear, float* ZFar);

	ModulesList GetType() override;

	Object* GetParentObject() override;
	void SetParentObject(const Object& parent) override;

	float GetFov();
	float GetAspect();
	float GetZNear();
	float GetZFar();

	Vector3 GetDirectionOfView();
	glm::mat4x4 GetProjectionMatrix();
	glm::mat4x4 GetTransformMatrix();
	
#pragma region Redifine from Transfom
	void AddPosition(float X, float Y, float Z) override;
	void AddPosition(Vector3 position) override;

	void SetPosition(float X, float Y, float Z) override;
	void SetPosition(Vector3 position) override;

	void AddRotation(float X, float Y, float Z) override;
	void AddRotation(Vector3 rotation) override;

	void SetRotation(float X, float Y, float Z) override;
	void SetRotation(Vector3 rotation) override;

	void ApplyTransformation() override;
#pragma endregion

	void UpdateProjectionMatrix();
	void UpdateViewMatrix();

	friend class Render;
	friend class ShaderProgram;

	Camera();
	~Camera();
};