#include "PhysicsEngine.h"

#include "Core/Objects/GameObject.h"
#include "Core/World.h"
#include "Core/Logger/Logger.h"

#include "AxisEngine/Buffers/CollidersBuffer.h"
#include "AxisEngine/Buffers/RigidBodiesBuffer.h"

namespace AxisEngine {
	PhysicsEngine::PhysicsEngine(size_t order) : System({ "RigidBodiesBuffer" }, order) {}

	void PhysicsEngine::EntryPoint(std::vector<Core::SystemData*>& data) {
		if (data[0] == nullptr) {
			Core::Logger::LogError("Data was null: " + __LOGERROR__);
			return;
		}

		auto* rigidBodiesBuffer = reinterpret_cast<RigidBodiesBuffer*>(data[0]);

		//PhysicsEngine::PullingVectorsLoop(*rigidBodiesBuffer);

		for (auto& rigidBody : rigidBodiesBuffer->_data) {
			if (rigidBody == nullptr)
				continue;

			PhysicsEngine::ApplyPhysics(*rigidBody);
		}
	}

	void PhysicsEngine::PullingVectorsLoop(AxisEngine::RigidBodiesBuffer& rigidBodiesBuffer) {
		for (auto& rigidBody : rigidBodiesBuffer._data) {
			if (rigidBody == nullptr)
				continue;

			//Physics::ApplyBaseFriction(*rigidBody);
			rigidBody->ApplyPullingVectors();
		}
	}

	void PhysicsEngine::ApplyGravity(RigidBody& rb) {
		rb.AddForce(rb.Gravity * rb.Mass);
	}
	void PhysicsEngine::ApplyBaseFriction(RigidBody& rb) {
		rb._linearVelocity *= rb.BaseFriction;
	}

	void PhysicsEngine::ApplyTorque(RigidBody& rb) {

		glm::vec3 scale = rb.GetParentObject()->transform.GetScale();

		constexpr float factor = 1.0 / 12.0;
		glm::mat3 I_local(0.0f);

		/*I_local[0][0]*/ float I1 = factor * rb.Mass * (glm::pow(scale.y, 2) + glm::pow(scale.z, 2));
		/*I_local[1][1]*/ float I2 = factor * rb.Mass * (glm::pow(scale.x, 2) + glm::pow(scale.z, 2));
		/*I_local[2][2]*/ float I3 = factor * rb.Mass * (glm::pow(scale.x, 2) + glm::pow(scale.y, 2));
	}

	void PhysicsEngine::ApplyPhysics(RigidBody& rb) {
		switch (_integrateMethod)
		{
		case IntegrateMethods::SemiImplicitEuler:
			PhysicsEngine::SemiImplicitIntegrate(rb);
			break;
		case IntegrateMethods::RK4:
			PhysicsEngine::RK4Integrate(rb);
			break;
		default:
			break;
		}
	}

	void PhysicsEngine::SemiImplicitIntegrate(RigidBody& rb) {
		double accumulator = Core::World::GetDeltaTime();
		if (accumulator > _maxTimeStep)
			accumulator = PhysicsEngine::_fixTimeStep;

		while (accumulator >= PhysicsEngine::_fixTimeStep)
		{
			PhysicsEngine::ApplyGravity(rb);
			PhysicsEngine::ApplyBaseFriction(rb);

			glm::vec3 acceleration = rb._force / rb.Mass;

			glm::vec3 newVelocity = rb.GetVelocity() + acceleration * PhysicsEngine::_fixTimeStep;

			if (glm::length(newVelocity) > rb.MaxSpeed) {
				rb._linearVelocity = glm::normalize(newVelocity) * rb.MaxSpeed;
			}
			else
			{
				rb._linearVelocity = newVelocity;			
			}

			rb.GetParentObject()->transform.AddPosition(rb.GetVelocity() * PhysicsEngine::_fixTimeStep);

			//if (glm::length2(rb._angularAcceleration) > 0) {
			//	rb.GetParentObject()->transform.AddRotation(-rb._angularAcceleration * PhysicsEngine::_fixTimeStep);
			//}
			ApplyTorque(rb);

			
			rb._force = { 0,0,0 };

			accumulator -= PhysicsEngine::_fixTimeStep;
		}

		if (accumulator != 0) {
			const double alpha = accumulator / PhysicsEngine::_fixTimeStep;

			PhysicsEngine::ApplyGravity(rb);
			PhysicsEngine::ApplyBaseFriction(rb);

			glm::vec3 acceleration = rb._force / rb.Mass;
			glm::vec3 newVelocity = rb.GetVelocity() + acceleration * PhysicsEngine::_fixTimeStep;

			rb._linearVelocity = glm::mix(rb._linearVelocity, newVelocity, (float)alpha);

			glm::vec3 deltaPos = rb.GetVelocity() * (float)(PhysicsEngine::_fixTimeStep * alpha);
			rb.GetParentObject()->transform.AddPosition(deltaPos);

			rb._force = { 0,0,0 };
		}

		rb._force = { 0,0,0 };
	}

	void PhysicsEngine::RK4Integrate(RigidBody& rb) {
		auto evaluate = [](const State& initial, float dt, const Derivative& d, glm::vec3 force, float mass) {
			State state;
			state.Position = initial.Position + d.dx * dt;
			state.Velocity = initial.Velocity + d.dv;

			Derivative output;
			output.dx = state.Velocity;
			output.dv = force / mass;
			return output;
			};

		auto integrate = [evaluate](State& state, float dt, glm::vec3 force, float mass)
			{
				Derivative a, b, c, d;

				a = evaluate(state, 0.0f, Derivative(), force, mass);
				b = evaluate(state, dt * 0.5f, a, force, mass);
				c = evaluate(state, dt * 0.5f, b, force, mass);
				d = evaluate(state, dt, c, force, mass);

				glm::vec3 dxdt = (a.dx + (b.dx + c.dx) * 2.0f + d.dx) * (1.0f / 6.0f);
				glm::vec3 dvdt = (a.dv + (b.dv + c.dv) * 2.0f + d.dv) * (1.0f / 6.0f);

				state.Position = state.Position + dxdt * dt;
				state.Velocity = state.Velocity + dvdt;
			};

		double accumulator = Core::World::GetDeltaTime();

		State state;
		state.Position = rb.GetParentObject()->transform.GetPosition();
		state.Velocity = rb._linearVelocity;

		while (accumulator >= PhysicsEngine::_fixTimeStep)
		{
			state.Position = rb.GetParentObject()->transform.GetPosition();
			state.Velocity = rb._linearVelocity;

			PhysicsEngine::ApplyGravity(rb);
			PhysicsEngine::ApplyBaseFriction(rb);

			integrate(state, PhysicsEngine::_fixTimeStep, rb._force, rb.Mass);

			rb._linearVelocity = state.Velocity;
			rb.GetParentObject()->transform.SetPosition(state.Position);

			accumulator -= PhysicsEngine::_fixTimeStep;
			rb._force = { 0,0,0 };
		}
		if (accumulator != 0) {
			const double alpha = accumulator / PhysicsEngine::_fixTimeStep;

			state.Position = rb.GetParentObject()->transform.GetPosition();
			state.Velocity = rb._linearVelocity;

			PhysicsEngine::ApplyGravity(rb);
			PhysicsEngine::ApplyBaseFriction(rb);

			integrate(state, PhysicsEngine::_fixTimeStep, rb._force, rb.Mass);

			rb._linearVelocity += (state.Velocity - rb._linearVelocity) * glm::vec3(alpha);
			rb.GetParentObject()->transform.AddPosition(state.Velocity * PhysicsEngine::_fixTimeStep * glm::vec3(alpha));

		}

		rb._force = { 0,0,0 };
	}
}