#pragma once

#include <vector>
#include <memory>

#include "Core/ECS/System.h"
#include "AxisEngine/Components/Rigidbody.h"

#include "AxisEngine/External/PhysX/cooking/PxCooking.h"
#include "AxisEngine/External/PhysX/PxPhysicsAPI.h"

namespace AxisEngine {
	class CollidersBuffer;
	class RigidBodiesBuffer;

	class RigidBody;
}

namespace AxisEngine {
	struct PxFoundationDeleter {
		void operator()(physx::PxFoundation* s) const noexcept {
			if (s) s->release();
		}
	};

	struct PxPhysicsDeleter {
		void operator()(physx::PxPhysics* s) const noexcept {
			if (s) s->release();
		}
	};

	struct PxDefaultCpuDispatcherDeleter {
		void operator()(physx::PxDefaultCpuDispatcher* s) const noexcept {
			if (s) s->release();
		}
	};

	struct PxSceneDeleter {
		void operator()(physx::PxScene* s) const noexcept {
			if (s) s->release();
		}
	};
}

namespace AxisEngine {
	class PhysicsEngine final : public Core::System {
	private:
		float _elasped = 0;

		const uint16_t _simulationSpeed = 60;

		const float _fixTimeStep = 1.0f / _simulationSpeed;
		const float _maxTimeStep = 1.0f / 10.0f;

		std::unique_ptr<physx::PxDefaultAllocator> _gAllocator = nullptr;
		std::unique_ptr<physx::PxDefaultErrorCallback> _gErrorCallback = nullptr;

		std::unique_ptr<physx::PxFoundation, PxFoundationDeleter> _foundation = nullptr;
		std::unique_ptr<physx::PxPhysics, PxPhysicsDeleter> _physics = nullptr;

		std::unique_ptr<physx::PxSceneDesc> _sceneDesc = nullptr;

		std::unique_ptr<physx::PxDefaultCpuDispatcher, PxDefaultCpuDispatcherDeleter> _dispatcher = nullptr;
		std::unique_ptr<physx::PxScene, PxSceneDeleter> _scene = nullptr;

	private:
		void InitPhysX();

		void EntryPoint(std::vector<Core::SystemData*>& data) override;

		void ApplyPhysics(RigidBody& rb);

	public:
		PhysicsEngine(size_t order);
		~PhysicsEngine() override = default;

		[[nodiscrad]] physx::PxPhysics* GetPhysics() const noexcept;
		[[nodiscrad]] physx::PxScene* GetScene() const noexcept;
	};
}