#include "Rigidbody.h"

#include "AxisEngine/Systems/PhysicsEngine.h"
#include "AxisEngine/Components/Collider.h"

#include "Core/World.h"
#include "Core/Logger/Logger.h"
#include "Core/Objects/Object.h"
#include "Core/Objects/GameObject.h"

namespace AxisEngine {
	RigidBody::RigidBody(PhysicsEngine& engine) {
		_physics = engine.GetPhysics();
		_scene = engine.GetScene();
	}

	bool RigidBody::CheckAddPossibility(Core::Object& newParent) {
		auto rbs = newParent.GetComponentByType<RigidBody>();
		if (rbs == nullptr) {
			return true;
		}
		Core::Logger::LogError("Object " + newParent.GetName() + " already has rigidbody. " + __LOGERROR__);
		return false;
	}

	void RigidBody::UpdateParentObject(Core::Object& newParent) {

		if (_pxDynamicRigidBody == nullptr) {
			auto pos = newParent.transform.GetPosition();
			auto rot = newParent.transform.GetRotationQuat();

			physx::PxTransform pose(
				physx::PxVec3(pos.x, pos.y, pos.z),
				physx::PxQuat(rot.x, rot.y, rot.z, rot.w)
			);

			_pxDynamicRigidBody.reset(_physics->createRigidDynamic(pose));

			_scene->addActor(*_pxDynamicRigidBody);
		}

#pragma region Detach_Shapes
		auto* oldParent = GetParentObject();
		if (oldParent != nullptr) {
			auto colliders = oldParent->GetComponentsByType<Collider>();

			for (auto& collider : colliders)
			{
				auto& shape = collider.get()._shape;
				//TODO: Check for shape actor doesn't belong other RigidBody
				if (shape->getActor() != nullptr) {
					_pxDynamicRigidBody->detachShape(*shape);
				}
			}
		}
#pragma endregion

		//Clear velociies
		_pxDynamicRigidBody->setLinearVelocity(physx::PxVec3(0, 0, 0));
		_pxDynamicRigidBody->setAngularVelocity(physx::PxVec3(0, 0, 0));

#pragma region Update_Transform_and_Velocity
		auto newPosition = newParent.transform.GetPosition();
		auto newRotationQuat = newParent.transform.GetRotationQuat();

		_transform.p = physx::PxVec3(newPosition.x, newPosition.y, newPosition.z);
		_transform.q = physx::PxQuat(newRotationQuat.x, newRotationQuat.y, newRotationQuat.z, newRotationQuat.w);

		_pxDynamicRigidBody->setGlobalPose(physx::PxTransform(_transform.p, _transform.q));
#pragma endregion

#pragma region Attach_Shapes
		auto colliders = newParent.GetComponentsByType<Collider>();

		for (auto& collider : colliders)
		{
			collider.get().ResetShape();
			auto& shape = collider.get()._shape;

			_pxDynamicRigidBody->attachShape(*shape);
			shape->release();
		}
#pragma endregion

		physx::PxRigidBodyExt::updateMassAndInertia(*_pxDynamicRigidBody, _mass);

		_pxDynamicRigidBody->wakeUp();
	}

	void RigidBody::AddForce(const glm::vec3& forceVector) {
		_pxDynamicRigidBody->addForce(physx::PxVec3(forceVector.x, forceVector.y, forceVector.z));
	}
	void RigidBody::AddForce(float x, float y, float z) {
		_pxDynamicRigidBody->addForce(physx::PxVec3(x, y, z));
	}

	void RigidBody::AddTorque(const glm::vec3& forceVector) {
		_pxDynamicRigidBody->addTorque(physx::PxVec3(forceVector.x, forceVector.y, forceVector.z));
	}
	void RigidBody::AddTorque(float x, float y, float z) {
		_pxDynamicRigidBody->addTorque(physx::PxVec3(x, y, z));
	}

	glm::vec3 RigidBody::GetLinearVelocity() const {
		auto vel = _pxDynamicRigidBody->getLinearVelocity();
		return { vel.x, vel.y, vel.z };
	}
	glm::vec3 RigidBody::GetAngularVelocity() const {
		auto vel = _pxDynamicRigidBody->getAngularVelocity();
		return { vel.x, vel.y, vel.z };
	}

	physx::PxRigidDynamic* RigidBody::GetRigidActor() const noexcept {
		return _pxDynamicRigidBody.get();
	}
}
