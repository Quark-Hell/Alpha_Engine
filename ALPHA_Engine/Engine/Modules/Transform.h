#pragma once
#include "Basical_Type.h"
#include "Module.h"

class Transform {
protected:
	Vector3 _position{ 0,0,0 };
	Vector4 _rotation{ 0,0,0,1 };
	Vector3 _scale{ 0,0,0 };

	Vector3 _origin{ 0,0,0 };

	bool _isShifted = false;
	glm::mat4x4 _transformMatrix{};

public:
	Transform();
	virtual ~Transform() = 0;

	virtual Vector3 GetPosition();
	virtual void AddPosition(float X, float Y, float Z);
	virtual void AddPosition(Vector3 position);

	virtual void SetPosition(float X, float Y, float Z);
	virtual void SetPosition(Vector3 position);


	virtual Vector4 GetRotation();
	virtual void AddRotation(float X, float Y, float Z);
	virtual void AddRotation(Vector3 rotation);

	virtual void SetRotation(float X, float Y, float Z);
	virtual void SetRotation(Vector3 rotation);


	virtual Vector3 GetScale();
	virtual void SetScale(float X, float Y, float Z);
	virtual void SetScale(Vector3 scale);

	virtual void AddOriginPosition(float X, float Y, float Z);
	virtual void AddOriginPosition(Vector3 position);
	
	virtual void SetOriginPosition(float X, float Y, float Z);
	virtual void SetOriginPosition(Vector3 position);

	virtual glm::mat4x4 GetTransformMatrix();

public:
	virtual void ApplyTransformation() = 0;
};