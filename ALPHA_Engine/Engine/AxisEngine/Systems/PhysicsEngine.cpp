#include "PhysicsEngine.h"

#include "Core/Objects/GameObject.h"
#include "Core/World.h"
#include "Core/Logger/Logger.h"

#include "AxisEngine/Buffers/CollidersBuffer.h"
#include "AxisEngine/Buffers/RigidBodiesBuffer.h"

namespace AxisEngine {
	PhysicsEngine::PhysicsEngine(size_t order) : System({ "RigidBodiesBuffer", "CollidersBuffer"}, order) {
		InitPhysX();
	}

	void PhysicsEngine::InitPhysX() {
		_gAllocator = std::make_unique<physx::PxDefaultAllocator>();
		_gErrorCallback = std::make_unique<physx::PxDefaultErrorCallback>();
		
		_foundation.reset(PxCreateFoundation(PX_PHYSICS_VERSION, *_gAllocator, *_gErrorCallback));
		if (!_foundation) {
			Core::Logger::LogCritical("PxCreateFoundation failed " + __LOGERROR__);
		}

		physx::PxPvd* pvd = physx::PxCreatePvd(*_foundation);
		physx::PxPvdTransport* transport =
			physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);

		pvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);

		Core::Logger::LogInfo("PVD connected");
		
		_physics.reset(PxCreatePhysics(PX_PHYSICS_VERSION, *_foundation, physx::PxTolerancesScale(), true, pvd));
		if (!_physics) {
			Core::Logger::LogCritical("PxCreatePhysics failed " + __LOGERROR__);
		}

		_sceneDesc = std::make_unique<physx::PxSceneDesc>(_physics->getTolerancesScale());
		_sceneDesc->gravity = physx::PxVec3(0.0f, -9.81f, 0.0f);

		_dispatcher.reset(physx::PxDefaultCpuDispatcherCreate(2));
		_sceneDesc->cpuDispatcher = _dispatcher.get();
		_sceneDesc->filterShader = physx::PxDefaultSimulationFilterShader;

		_scene.reset(_physics->createScene(*_sceneDesc));

		Core::Logger::LogInfo("PhysX scene created");

		Core::Logger::LogInfo("PhysX started succesfully. PhysX version: ",
			PX_PHYSICS_VERSION_MAJOR, ".",
			PX_PHYSICS_VERSION_MINOR);
	}

	void PhysicsEngine::EntryPoint(std::vector<Core::SystemData*>& data) {
		if (data[0] == nullptr || data[1] == nullptr) {
			Core::Logger::LogError("Data was null: " + __LOGERROR__);
			return;
		}

		auto* collidersBuffer = reinterpret_cast<CollidersBuffer*>(data[1]);
		for (auto& collider : collidersBuffer->_data) {
			if (collider == nullptr && collider->_shape == nullptr)
				continue;

			collider->UpdateScale();
		}

		auto* rigidBodiesBuffer = reinterpret_cast<RigidBodiesBuffer*>(data[0]);

		for (auto& rigidBody : rigidBodiesBuffer->_data) {
			if (rigidBody == nullptr || !rigidBody->_pxDynamicRigidBody)
				continue;

			if (rigidBody->_pxDynamicRigidBody->getScene() != _scene.get()) {
				_scene->addActor(*rigidBody->_pxDynamicRigidBody);
				Core::Logger::LogInfo("Added rigid body to scene");
			}

			rigidBody->UpdatePhysXTransform();

			if(rigidBody->GetRigidBodyType() == AxisEngine::RigidBodyType::Dynamic)
				rigidBody->_pxDynamicRigidBody->wakeUp();
		}

		double elapsed = Core::World::GetDeltaTime();
		_elasped += elapsed;

		while (_elasped - _fixTimeStep >= 0) {
			_elasped -= _fixTimeStep;

			_scene->simulate(_fixTimeStep);
			_scene->fetchResults(true);
		}

		for (auto& rigidBody : rigidBodiesBuffer->_data) {
			if (rigidBody == nullptr)
				continue;

			rigidBody->UpdateObjectTransform();
		}
	}

	void PhysicsEngine::ApplyPhysics(RigidBody& rb) {

	}

	physx::PxPhysics* PhysicsEngine::GetPhysics() const noexcept {
		return _physics.get();
	}

	physx::PxScene* PhysicsEngine::GetScene() const noexcept {
		return _scene.get();
	}
}