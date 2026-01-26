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
		if (!_pxDynamicRigidBody) {
			if (auto* parent = GetParentObject()) {
				auto colliders = parent->GetComponentsByType<Collider>();

				for (auto& collider : colliders)
				{
					auto& shape = collider.get()._shape;
					_pxDynamicRigidBody->detachShape(*shape);

				}

				_pxDynamicRigidBody.reset(PxCreateDynamic(_physics, _transform, _geometry, *_material, 10.0f));
			}
		}

		auto newPos = newParent.transform.GetPosition();
		auto newRot = newParent.transform.GetRotationQuat();

		_transform.p = physx::PxVec3(newPos.x, newPos.y, newPos.z);
		_transform.q = physx::PxQuat(newRot.x, newRot.y, newRot.z, newRot.w);

		_pxDynamicRigidBody->setLinearVelocity(physx::PxVec3(0,0,0));
		_pxDynamicRigidBody->setAngularVelocity(physx::PxVec3(0, 0, 0));

		_pxDynamicRigidBody.reset(PxCreateDynamic(_physics, _transform, _geometry, *_material, 10.0f));


		auto colliders = newParent.GetComponentsByType<Collider>();

		for (auto& collider : colliders)
		{
			auto& shape = collider.get()._shape;
			_pxDynamicRigidBody->attachShape(*shape);

		}
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