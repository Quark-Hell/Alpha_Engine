#pragma once
#include "Basical_Type.h"
#include "Module.h"
class Vector3;
class Geometry;

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
	Vector3 Gravity = Vector3{ 0,-1.81,0 };
	float BaseFriction = 0.9;
	/*Description:
	if = 1 than body movement reflect
	if = 0 than body stop*/
	float ElasticityCoefficient = 0;
	float MaxSpeed = 20;

private:
	Vector3 _force{ 0,0,0 };
	//Vector3 _acceleration{ 0,0,0 };
	Vector3 _velocity{ 0,0,0 };

	Vector3 _centerMass;

	Vector3 _rotationVector{ 0,0,0 };
	Vector4 _orientation{ 0,0,0 };
	Vector3 _angularMomentum{ 0,0,0 };
	Vector3 _angularVelocity{ 0,0,0 };

	std::vector<Vector3> _contactPoints;
	std::vector<Vector3> _pullingVectors;

	bool _hasCollision;
	//Matrix3x3 _inertiaMatrix;

public:
	void AddForce(const Vector3& forceVector);
	void AddForce(const float& x, const float& y, const float& z);

	void AddAngularMomentum(const Vector3& forceVector, Vector3 relativePoint);
	void AddAngularMomentum(const float& x, const float& y, const float& z, Vector3 relativePoint);

	//void SetInertiaMatrix(Matrix3x3 matrix);
	//void ResetInertiaMatrix();
	//Matrix3x3 GetInertiaMatrix();

	ModulesList GetType() override;

	void CalculateCenterMass();

	Vector3 GetCenterMass();
	Vector3 GetVelocity();
	Vector3 GetForce();
	Vector3 GetPosition();

	Object* GetParentObject() override;
	void SetParentObject(const Object& parent) override;

	bool GetContactPoints(std::vector<Vector3>& contactPoint);

	RigidBody();
	~RigidBody();

private:
	void SetMovementVector(Vector3 vec);
	void SetRotationVector(Vector3 vec);

	void AddContactPoints(std::vector<Vector3>& points);

	void ClearCollisinInfo();

	void ApplyPullingVectors();

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

	static inline IntegrateMethods IntegrateMethod = IntegrateMethods::SemiImplicitEuler;

private:
	static inline const float fixTimeStep = 1.0f / 60.0f;
	static inline const float _maxTimeStep = 1.0f / 10.0f;

public:
	static void PhysicsLoop();
	static void PullingVectorsLoop();

	Physics();
	~Physics();

private:
	static void ApplyGravity(RigidBody& rb);
	static void ApplyBaseFriction(RigidBody& rb);
	static void ApplyTorque(RigidBody& rb);

	static void Contact(RigidBody& rb1, Vector3 contactNormal = 0);
	static void Contact(RigidBody& rb1, RigidBody& rb2, Vector3 contactNormal = 0);

	static void ApplyPhysics(RigidBody& rb);
	static void ApplyVelocity(RigidBody& rb);

	static void SemiImplicitIntegrate(RigidBody& rb);
	static void RK4Integrate(RigidBody& rb);

	friend class Collision;
};