#pragma once

#include <vector>

#include "Core/ECS/System.h"
#include "AxisEngine/Components/Rigidbody.h"

namespace AxisEngine {
	class CollidersBuffer;
	class RigidBodiesBuffer;
}

namespace AxisEngine {
	enum class IntegrateMethods {
		SemiImplicitEuler = 0,
		RK4 = 1
	};

	class State {
	public:
		glm::vec3 Position;
		glm::vec3 Velocity;
	};
	class Derivative {
	public:
		glm::vec3 dx;
		glm::vec3 dv;
	};

	class PhysicsEngine final : public Core::System {
	private:
		const uint16_t _simulationSpeed = 60;
		const IntegrateMethods _integrateMethod = IntegrateMethods::SemiImplicitEuler;

		const float _fixTimeStep = 1.0f / 60.0f;
		const float _maxTimeStep = 1.0f / 10.0f;

	private:
		void EntryPoint(std::vector<Core::SystemData*>& data) override;

		void PullingVectorsLoop(AxisEngine::RigidBodiesBuffer& rigidBodiesBuffer);

		void ApplyGravity(RigidBody& rb);
		void ApplyBaseFriction(RigidBody& rb);

		void ApplyTorque(RigidBody& rb);

		void Contact(RigidBody& rb1, glm::vec3 contactNormal);
		void Contact(RigidBody& rb1, RigidBody& rb2, glm::vec3 contactNormal);


		void ApplyPhysics(RigidBody& rb);

		void SemiImplicitIntegrate(RigidBody& rb);

		void RK4Integrate(RigidBody& rb);

	public:
		PhysicsEngine(size_t order);
		~PhysicsEngine() override = default;
	};
}