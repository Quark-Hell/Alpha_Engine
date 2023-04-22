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
	if (RigidBody::_movementVector < Vector3{0.5,0.5,0.5}) {
		RigidBody::_movementVector += forceVector;
	}
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
	RigidBody::Rename("RigidBody");

	//RigidBody::CalculateCenterMass();
}

inline RigidBody::~RigidBody() {

}
#pragma endregion

#pragma region Phisycs Define
inline void Physics::PhysicsLoop() {
	for (size_t it = 0; it < World::ObjectsOnScene.size(); it++)
	{
		Object* obj = World::ObjectsOnScene[it];
		RigidBody* rigidBody;

		for (size_t i = 0; i < obj->GetCountOfModules(); i++)
		{
			rigidBody = dynamic_cast<RigidBody*>(obj->GetModuleByIndex(i));
			if (rigidBody != NULL) {
				Physics::ApplyGravity(*rigidBody);
				Physics::ApplyPhysics(*rigidBody);

				std::cout << rigidBody->GetImpulseVector().Y;
				std::cout << World::_deltaTime / 1000;
				std::cout << "\n";

				break;
			}
		}
	}
}

inline void Physics::ApplyGravity(RigidBody& rb) {
	rb.AddForceWithoutMass((rb.GetImpulseVector() + rb.Gravity * World::SimulationSpeed) * (World::_deltaTime / 1000));
}

inline void Physics::ApplyPhysics(RigidBody& rb) {
	rb.GetParentObject()->AddPosition(rb.GetImpulseVector());
}

inline Physics::Physics() {

}
inline Physics::~Physics() {

}