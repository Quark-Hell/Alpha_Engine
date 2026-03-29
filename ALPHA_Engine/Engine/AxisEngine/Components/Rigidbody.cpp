#include "Rigidbody.h"

#include "AxisEngine/Systems/PhysicsEngine.h"
#include "AxisEngine/Components/Collider.h"

#include "Core/World.h"
#include "Core/Logger/Logger.h"
#include "Core/Objects/Object.h"
#include "Core/Objects/GameObject.h"

namespace AxisEngine {
	RigidBody::RigidBody(PhysicsEngine& engine, AxisEngine::RigidBodyType rigidBodyType) {
		_physics = engine.GetPhysics();
		_scene = engine.GetScene();

		_rigidBodyType = rigidBodyType;

		Core::Logger::LogInfo("RigidBody created");
	}

	bool RigidBody::CheckAddPossibility(Core::Object& newParent) {
		auto rbs = newParent.GetComponentByType<RigidBody>();
		if (rbs == nullptr) {
			return true;
		}
		Core::Logger::LogError("Object " + newParent.GetName() + " already has rigidbody. " + __LOGERROR__);
		return false;
	}

	void RigidBody::UpdateStatic(Core::Object& newParent) {
		if (_pxStaticRigidBody == nullptr) {
			auto pos = newParent.transform.GetPosition();
			auto rot = newParent.transform.GetRotationQuat();

			physx::PxTransform pose(
				physx::PxVec3(pos.x, pos.y, pos.z),
				physx::PxQuat(rot.x, rot.y, rot.z, rot.w)
			);

			_pxStaticRigidBody.reset(_physics->createRigidStatic(pose));

			_scene->addActor(*_pxStaticRigidBody);
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
					_pxStaticRigidBody->detachShape(*shape);
				}
			}
		}
#pragma endregion

#pragma region Update_Transform_and_Velocity
		auto newPosition = newParent.transform.GetPosition();
		auto newRotationQuat = newParent.transform.GetRotationQuat();

		_transform.p = physx::PxVec3(newPosition.x, newPosition.y, newPosition.z);
		_transform.q = physx::PxQuat(newRotationQuat.x, newRotationQuat.y, newRotationQuat.z, newRotationQuat.w);

		_pxStaticRigidBody->setGlobalPose(physx::PxTransform(_transform.p, _transform.q));
#pragma endregion

#pragma region Attach_Shapes
		auto colliders = newParent.GetComponentsByType<Collider>();

		for (auto& collider : colliders)
		{
			collider.get().ResetShape();
			auto& shape = collider.get()._shape;

			_pxStaticRigidBody->attachShape(*shape);
			shape->release();
		}
#pragma endregion
	}

	void RigidBody::UpdateKinematic(Core::Object& newParent) {
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

		_pxDynamicRigidBody->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, true);

#pragma region Detach_Shapes
		auto* oldParent = GetParentObject();
		if (oldParent != nullptr) {
			auto colliders = oldParent->GetComponentsByType<Collider>();

			for (auto& collider : colliders)
			{
				auto& shape = collider.get()._shape;
				//TODO: Check for shape actor doesn't belong other RigidBody
				if (shape != nullptr && shape->getActor() != nullptr) {
					_pxDynamicRigidBody->detachShape(*shape);
				}
			}
		}
#pragma endregion

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
	}


	void RigidBody::UpdateDynamic(Core::Object& newParent) {
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

	void RigidBody::OnParentObjectChanged(Core::Object& newParent) {
		switch (_rigidBodyType) {

		case AxisEngine::RigidBodyType::Static:
			UpdateStatic(newParent);
			break;

		case AxisEngine::RigidBodyType::Kinematic:
			UpdateKinematic(newParent);
			break;

		case AxisEngine::RigidBodyType::Dynamic:
			UpdateDynamic(newParent);
			break;
		}
	}

	void RigidBody::UpdateObjectTransform() {
		if (_rigidBodyType == AxisEngine::RigidBodyType::Static) {
			Core::Logger::LogError("Cannot update rigidbody transform. RigidBody type is STATIC", __LOGERROR__);
			return;
		}

		if (_pxDynamicRigidBody == nullptr) { 
			Core::Logger::LogError("Cannot update rigidbody transform. PhysX instance of RigidBody was null", __LOGERROR__);
			return; 
		}

		Core::Object* obj = _parentObject;
		if (obj == nullptr) {
			Core::Logger::LogError("Cannot update rigidbody transform. Parent object was null", __LOGERROR__);
			return;
		}

		auto physXpose = _pxDynamicRigidBody->getGlobalPose();

		glm::vec3 physXvec = glm::vec3(physXpose.p.x, physXpose.p.y, physXpose.p.z);
		glm::quat physXquat = glm::quat(physXpose.q.w, physXpose.q.x, physXpose.q.y, physXpose.q.z);

		obj->transform.SetPosition(physXvec);
		obj->transform.SetRotationQuat(physXquat);
	}

	void RigidBody::UpdatePhysXTransform() {
		if (_rigidBodyType == AxisEngine::RigidBodyType::Static) {
			Core::Logger::LogError("Cannot update rigidbody transform. RigidBody type is STATIC", __LOGERROR__);
			return;
		}

		if (_pxDynamicRigidBody == nullptr) {
			Core::Logger::LogError("Cannot update rigidbody transform. PhysX instance of RigidBody was null", __LOGERROR__);
			return;
		}

		Core::Object* obj = _parentObject;
		if (obj == nullptr) {
			Core::Logger::LogError("Cannot update rigidbody transform. Parent object was null", __LOGERROR__);
			return;
		}

#pragma region Update_Pose
		glm::vec3 objPos = obj->transform.GetPosition();
		glm::quat objQuat = obj->transform.GetRotationQuat();

		physx::PxTransform pose = _pxDynamicRigidBody->getGlobalPose();

		pose.p = physx::PxVec3(objPos.x, objPos.y, objPos.z);
		pose.q = physx::PxQuat(objQuat.x, objQuat.y, objQuat.z, objQuat.w);
		pose.q.normalize();

		if (_rigidBodyType == AxisEngine::RigidBodyType::Kinematic)
			_pxDynamicRigidBody->setKinematicTarget(pose);
		else
			_pxDynamicRigidBody->setGlobalPose(pose);
#pragma endregion
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

	[[nodiscard]] RigidBodyType RigidBody::GetRigidBodyType() const noexcept {
		return _rigidBodyType;
	}
}
