#pragma once

class RigidBody : public Module {
public:
	float Mass = 1;
	Vector3 Gravity = Vector3{ 0,-0.5,0 };

private:
	Vector3 _centerMass;

	Vector3 _rotationVector{0,0,0};
	Vector3 _movementVector{0,0,0};

public:
	void AddForce(const Vector3& forceVector);
	void AddForce(const float& x, const float& y, const float& z);

	void AddForceWithoutMass(const Vector3& forceVector);

	void CalculateCenterMass();

	Vector3 GetCenterMass();
	Vector3 GetImpulseVector();

	RigidBody();
	~RigidBody();

private:
	void SetMovementVector(Vector3 vec);
	void SetRotationVector(Vector3 vec);

	friend class Collision;
};

class Physics {
public:
	void PhysicsLoop();

	Physics();
	~Physics();

private:
	void ApplyGravity(RigidBody& rb);

	void ApplyPhysics(RigidBody& rb);

};