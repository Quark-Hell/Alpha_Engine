#include "Physics.h"

#include "Basical_Type.h"
#include "Geometry.h"
#include "World.h"

inline void RigidBody::AddForce(const Vector3& forceVector) {
	RigidBody::_movementVector += forceVector * RigidBody::Mass;
}
inline void RigidBody::AddForce(const float& x, const float& y, const float& z) {
	RigidBody::_movementVector += Vector3(x, y, z) * RigidBody::Mass;
}

inline void RigidBody::AddForceWithoutMass(const Vector3& forceVector) {
	RigidBody::_movementVector += forceVector;
}

inline ModulesList RigidBody::GetType() {
	return ModulesList::RigidBodyType;
}

inline void RigidBody::CalculateCenterMass() {
	Object* object = RigidBody::GetParentObject();
	RigidBody::_centerMass = Vector3(0, 0, 0);
	std::vector<Geometry*> geometries;

	for (size_t i = 0; i < object->GetCountOfModules(); i++)
	{
		Geometry* geometry = dynamic_cast<Geometry*>(object->GetModuleByIndex(i));
		if (geometry != nullptr) {
			geometries.push_back(geometry);
		}
	}

	float scope[6];
	//X
	scope[0] = FLT_MAX;
	scope[1] = -FLT_MAX;

	//Y
	scope[2] = FLT_MAX;
	scope[3] = -FLT_MAX;

	//Z
	scope[4] = FLT_MAX;
	scope[5] = -FLT_MAX;

	for (unsigned int it = 0; it < geometries.size(); it++) {
		for (unsigned int jt = 0; jt < geometries[it]->_vertexCount * 3; jt += 3) {
			//X
			if (geometries[it]->_vertex[jt] < scope[0]) {
				scope[0] = geometries[it]->_vertex[jt];
			}
			else if (geometries[it]->_vertex[jt] > scope[1]) {
				scope[1] = geometries[it]->_vertex[jt];
			}

			//Y
			if (geometries[it]->_vertex[jt + 1] < scope[2]) {
				scope[2] = geometries[it]->_vertex[jt + 1];
			}
			else if (geometries[it]->_vertex[jt + 1] > scope[3]) {
				scope[3] = geometries[it]->_vertex[jt + 1];
			}

			//Z
			if (geometries[it]->_vertex[jt + 2] < scope[4]) {
				scope[4] = geometries[it]->_vertex[jt + 2];
			}
			else if (geometries[it]->_vertex[jt + 2] > scope[5]) {
				scope[5] = geometries[it]->_vertex[jt + 2];
			}
		}

		float xScope = scope[1] - scope[0];
		float yScope = scope[3] - scope[2];
		float zScope = scope[5] - scope[4];

		RigidBody::_centerMass += Vector3(xScope, yScope, zScope) / 2;
	}

	RigidBody::_centerMass /= geometries.size();
}

inline Vector3 RigidBody::GetCenterMass() {
	return RigidBody::_centerMass;
}

inline Vector3 RigidBody::GetImpulseVector() {
	return RigidBody::_movementVector;
}

inline RigidBody::RigidBody() {


	//RigidBody::CalculateCenterMass();
}

inline RigidBody::~RigidBody() {

}
#pragma endregion

#pragma region Phisycs Define
inline void Physics::PhysicsLoop() {
	//TODO: Bug: the object sometimes is rapidly accelerating.
	// speed logs:
	// -0.181993
	// -0.191078
	// -0.54995          // WTF?
	// -0.547201
	// -0.544621

	for (size_t it = 0; it < World::ObjectsOnScene.size(); it++)
	{
		Object* obj = World::ObjectsOnScene[it];
		RigidBody* rigidBody;

		for (size_t i = 0; i < obj->GetCountOfModules(); i++)
		{
			rigidBody = dynamic_cast<RigidBody*>(obj->GetModuleByIndex(i));
			if (rigidBody != NULL) {
				Physics::ApplyGravity(*rigidBody);
				Physics::ApplyBaseFriction(*rigidBody);
				Physics::ApplyPhysics(*rigidBody);
				
				std::cout << rigidBody->_movementVector.X;
				std::cout << "\n";

				break;
			}
		}
	}
}

inline void Physics::ApplyGravity(RigidBody& rb) {
	Vector3 add = (rb.Gravity * 4 * World::SimulationSpeed * powf(World::_deltaTime / 1000, 2));
	rb.AddForceWithoutMass(add);

}
inline void Physics::Torque(RigidBody& rb, Vector3 colPoint) {

	//float angle = Vector3::GetAngle(rb.);
}

inline void Physics::Contact(RigidBody& rb1, Vector3 contactNormal) {
	contactNormal.NormilizeSelf();
	Math::RemoveError(contactNormal);

	float u1 = Vector3::DotProduct(rb1._movementVector, contactNormal);
	Vector3 newRb1Vector = rb1._movementVector + contactNormal * (2 * 1 * (0 - u1) / (rb1.Mass + 0)) * rb1.ElasticityCoefficient;

	rb1._movementVector = newRb1Vector;
}
inline void Physics::Contact(RigidBody& rb1, RigidBody& rb2, Vector3 contactNormal) {
	contactNormal.NormilizeSelf();
	Math::RemoveError(contactNormal);

	float u1 = Vector3::DotProduct(rb1._movementVector, contactNormal);
	float u2 = Vector3::DotProduct(rb2._movementVector, contactNormal);

	Vector3 newRb1Vector = rb1._movementVector + contactNormal * (2 * rb2.Mass * (u2 - u1) / (rb1.Mass + rb2.Mass));
	Vector3 newRb2Vector = rb2._movementVector + contactNormal * (2 * rb1.Mass * (u1 - u2) / (rb2.Mass + rb1.Mass));

	rb1._movementVector = newRb1Vector;
	rb2._movementVector = newRb2Vector;
}

inline void Physics::ApplyBaseFriction(RigidBody& rb) {
	rb._movementVector *= rb.BaseFriction;
}

inline void Physics::ApplyPhysics(RigidBody& rb) {
	if (rb._movementVector.GetMagnitude() > rb.MaxSpeed) {
		Vector3::GetNormalize(rb._movementVector) *= rb._movementVector;

		rb.GetParentObject()->AddPosition(rb.GetImpulseVector());
	}
	else
	{
		rb.GetParentObject()->AddPosition(rb.GetImpulseVector());
	}

	//std::cout << rb._movementVector.Y;
	//std::cout << "\n";
}

inline Physics::Physics() {

}
inline Physics::~Physics() {

}