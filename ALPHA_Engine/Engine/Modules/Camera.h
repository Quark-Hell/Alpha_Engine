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
	
#pragma region Redifine from Transfom
	Vector3 GetPosition() override;
	void AddPosition(float X, float Y, float Z) override;
	void AddPosition(Vector3 position) override;

	void SetPosition(float X, float Y, float Z) override;
	void SetPosition(Vector3 position) override;


	Vector3 GetRotation() override;
	void AddRotation(float X, float Y, float Z) override;
	void AddRotation(Vector3 rotation) override;

	void SetRotation(float X, float Y, float Z) override;
	void SetRotation(Vector3 rotation) override;


	Vector3 GetScale() override;
	void SetScale(float X, float Y, float Z) override;
	void SetScale(Vector3 scale) override;

	void AddOriginPosition(float X, float Y, float Z) override;
	void AddOriginPosition(Vector3 position) override;

	void SetOriginPosition(float X, float Y, float Z) override;
	void SetOriginPosition(Vector3 position) override;

	void ApplyTransformation() override;
#pragma endregion

	void UpdateProjectionMatrix();
	void UpdateViewMatrix();

	friend class Render;

	Camera();
	~Camera();
};