#pragma once

class RigidBody : public Module {
public:
	float Mass = 1;
	Vector3 Gravity = Vector3{ 0,-9.81,0 };
	float BaseFriction = 0.995;
	/*Description:
	if = 1 than body movement reflect
	if = 0 than body stop*/
	float ElasticityCoefficient = 0.8;
	float MaxSpeed = 2;

private:
	Vector3 _centerMass;

	Vector3 _rotationVector{0,0,0};
	Vector3 _movementVector{0,0,0};

public:
	void AddForce(const Vector3& forceVector);
	void AddForce(const float& x, const float& y, const float& z);

	void AddForceWithoutMass(const Vector3& forceVector);
	ModulesList GetType() override;

	void CalculateCenterMass();

	Vector3 GetCenterMass();
	Vector3 GetImpulseVector();

	RigidBody();
	~RigidBody();

private:
	void SetMovementVector(Vector3 vec);
	void SetRotationVector(Vector3 vec);

	friend class Collision;
	friend class Physics;
};

class Physics {
public:
	static inline void PhysicsLoop();

	Physics();
	~Physics();

private:
	static inline void ApplyGravity(RigidBody& rb);
	static inline void ApplyBaseFriction(RigidBody& rb);
	static inline void Torque(RigidBody& rb, Vector3 colPoint);

	static inline void Contact(RigidBody& rb1, Vector3 contactNormal = 0);
	static inline void Contact(RigidBody& rb1, RigidBody& rb2, Vector3 contactNormal = 0);

	static inline void ApplyPhysics(RigidBody& rb);
	static inline void ApplyVelocity(RigidBody& rb);

	friend class Collision;
};