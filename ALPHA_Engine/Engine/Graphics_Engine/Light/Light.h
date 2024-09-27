#pragma once

#include "World.h"
#include "Modules/MovableModule.h"

class Light : public MovableModule {
protected:
	bool _instDelete = false;
	Vector3 _lookingPoint = Vector3(-1, 0, 0);

public:
	Vector3 color = Vector3(1, 1, 1);
	float strength = 1;

public:
	Light();
	virtual ~Light();

	ModulesList GetType() override;

#pragma region Redifine from Transfom
	void AddPosition(float X, float Y, float Z) override;
	void AddPosition(Vector3 position) override;

	void SetPosition(float X, float Y, float Z) override;
	void SetPosition(Vector3 position) override;


	void AddRotation(float X, float Y, float Z) override;
	void AddRotation(Vector3 rotation) override;

	void SetRotation(float X, float Y, float Z) override;
	void SetRotation(Vector3 rotation) override;


	void AddOriginPosition(float X, float Y, float Z) override;
	void AddOriginPosition(Vector3 position) override;

	void SetOriginPosition(float X, float Y, float Z) override;
	void SetOriginPosition(Vector3 position) override;

	void ApplyTransformation() override;
#pragma endregion

	Vector3 GetDirection();
};