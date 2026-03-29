#pragma once

#include <vector>
#include <memory>

#include "Core/Components/Component.h"
#include "glm/glm.hpp"

#include "PhysX/PxPhysicsAPI.h"

namespace Core {
	class Object;
}

namespace AxisEngine {
	struct PxRigidDynamicDeleter {
		void operator()(physx::PxRigidDynamic* s) const noexcept {
			if (s) s->release();
		}
	};

	struct PxRigidStaticDeleter {
		void operator()(physx::PxRigidStatic* s) const noexcept {
			if (s) s->release();
		}
	};
}

namespace AxisEngine {
	enum class RigidBodyType {
		Static, 
		Kinematic, 
		Dynamic
	};
}

namespace AxisEngine {
	class RigidBody final : public Core::Component {
		friend class PhysicsEngine;
		friend class CollisionEngine;

		friend class RigidBodiesBuffer;

	private:
		std::unique_ptr<physx::PxRigidDynamic, PxRigidDynamicDeleter> _pxDynamicRigidBody;
		std::unique_ptr<physx::PxRigidStatic, PxRigidStaticDeleter> _pxStaticRigidBody;

		physx::PxTransform _transform{ physx::PxVec3(0, 10, 0) };

		physx::PxPhysics* _physics;
		physx::PxScene* _scene;

		float _mass = 1.0f;
		RigidBodyType _rigidBodyType = RigidBodyType::Static;

	private:
		RigidBody(PhysicsEngine& engine, AxisEngine::RigidBodyType = AxisEngine::RigidBodyType::Static);

		void UpdateObjectTransform();
		void UpdatePhysXTransform();

		void UpdateStatic(Core::Object& newParent);
		void UpdateKinematic(Core::Object& newParent);
		void UpdateDynamic(Core::Object& newParent);

	protected:
		bool CheckAddPossibility(Core::Object& newParent) override;
		void OnParentObjectChanged(Core::Object& newParent) override;

	public:
        ~RigidBody() override = default;

		void AddForce(const glm::vec3& forceVector);
		void AddForce(float x, float y, float z);

		void AddTorque(const glm::vec3& forceVector);
		void AddTorque(float x, float y, float z);

		[[nodiscard]] RigidBodyType GetRigidBodyType() const noexcept;
		void SetRigidBodyType(RigidBodyType rigidBodyType);

		[[nodiscard]] glm::vec3 GetLinearVelocity() const;
		[[nodiscard]] glm::vec3 GetAngularVelocity() const;

		[[nodiscard]] physx::PxRigidDynamic* GetRigidActor() const noexcept;
	};
}

