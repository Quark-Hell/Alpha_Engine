#pragma once
class State {
public:
	Vector3 Position;
	Vector3 Velocity;
};
class Derivative {
public:
	Vector3 dx;
	Vector3 dv;
};

class RigidBody : public Module {
public:
	float Mass = 1;
	Vector3 Gravity = Vector3{ 0,-9.81,0 };
	float BaseFriction = 0.9;
	/*Description:
	if = 1 than body movement reflect
	if = 0 than body stop*/
	float ElasticityCoefficient = 0.8;
	float MaxSpeed = 20;

private:
	Vector3 _force{ 0,0,0 };
	//Vector3 _acceleration{ 0,0,0 };
	Vector3 _velocity{ 0,0,0 };

	Vector3 _centerMass;

	Vector3 _rotationVector{ 0,0,0 };

public:
	void AddForce(const Vector3& forceVector);
	void AddForce(const float& x, const float& y, const float& z);

	ModulesList GetType() override;

	void CalculateCenterMass();

	Vector3 GetCenterMass();
	Vector3 GetVelocity();
	Vector3 GetForce();
	Vector3 GetPosition();

	void SetParentObject(const Object& parent) override;

	RigidBody();
	~RigidBody();

private:
	void SetMovementVector(Vector3 vec);
	void SetRotationVector(Vector3 vec);

	friend class Collision;
	friend class Physics;
};
enum IntegrateMethods {
	SemiImplicitEuler = 0,
	RK4 = 1
};
static class Physics {



public:
	//60 frame per second
	const static inline unsigned int SimulationSpeed = 60;

	static inline IntegrateMethods IntegrateMethod = IntegrateMethods::RK4;

private:
	static inline const float fixTimeStep = 1.0f / 100.0f;

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

	static inline void SemiImplicitIntegrate(RigidBody& rb);
	static inline void RK4Integrate(RigidBody& rb);

	friend class Collision;
};