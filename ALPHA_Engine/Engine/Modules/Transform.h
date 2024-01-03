#pragma once
#include "Basical_Type.h"
#include "Module.h"

class Transform {
protected:
	Vector3 _position{ 0,0,0 };
	Vector4 _rotation{ 0,0,0,1 };
	Vector3 _scale{ 1,1,1 };

	Vector3 _origin{ 0,0,0 };

	glm::mat4x4 _transformMatrix{};

public:
	Transform();
	virtual ~Transform() = 0;

	virtual Vector3 GetPosition() = 0;
	virtual void AddPosition(float X, float Y, float Z) = 0;
	virtual void AddPosition(Vector3 position) = 0;

	virtual void SetPosition(float X, float Y, float Z) = 0;
	virtual void SetPosition(Vector3 position) = 0;


	virtual Vector3 GetRotation() = 0;
	virtual void AddRotation(float X, float Y, float Z) = 0;
	virtual void AddRotation(Vector3 rotation) = 0;

	virtual void SetRotation(float X, float Y, float Z) = 0;
	virtual void SetRotation(Vector3 rotation) = 0;


	virtual Vector3 GetScale() = 0;
	virtual void SetScale(float X, float Y, float Z) = 0;
	virtual void SetScale(Vector3 scale) = 0;

	virtual void AddOriginPosition(float X, float Y, float Z) = 0;
	virtual void AddOriginPosition(Vector3 position) = 0;
	
	virtual void SetOriginPosition(float X, float Y, float Z) = 0;
	virtual void SetOriginPosition(Vector3 position) = 0;

public:
	virtual void ApplyTransformation() = 0;
};