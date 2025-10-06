#include "AxisEngine.h"

#include "Core/Objects/GameObject.h"
#include "Core/World.h"
#include "Core/Logger/Logger.h"

#include "Buffers/CollidersBuffer.h"
#include "Buffers/RigidBodiesBuffer.h"

namespace AxisEngine {
	PhysicsEngine::PhysicsEngine() : System({ "CollidersBuffer", "RigidBodiesBuffer" }, 6000) {}

	void PhysicsEngine::EntryPoint(std::vector<Core::SystemData*>& data) {
		if (data[0] == nullptr || data[1] == nullptr) {
			Core::Logger::LogError("Data was null: " + __LOGERROR__);
			return;
		}

		auto* collidersBuffer = reinterpret_cast<CollidersBuffer*>(data[0]);
		auto* rigidBodiesBuffer = reinterpret_cast<RigidBodiesBuffer*>(data[1]);

		PhysicsEngine::PullingVectorsLoop(*rigidBodiesBuffer);
		PhysicsEngine::PhysicsLoop(*rigidBodiesBuffer);
	}

	void PhysicsEngine::PullingVectorsLoop(AxisEngine::RigidBodiesBuffer& rigidBodiesBuffer) {
		for (auto& rigidBody : rigidBodiesBuffer._data) {
			if (rigidBody == nullptr)
				continue;

			//Physics::ApplyBaseFriction(*rigidBody);
			rigidBody->ApplyPullingVectors();

			//std::cout << rigidBody->_movementVector.X;
			//std::cout << "\n";
		}
	}

	void PhysicsEngine::PhysicsLoop(AxisEngine::RigidBodiesBuffer& rigidBodiesBuffer) {
		for (auto& rigidBody : rigidBodiesBuffer._data) {
			if (rigidBody == nullptr)
				continue;

			PhysicsEngine::ApplyPhysics(*rigidBody);

			//std::cout << rigidBody->_movementVector.X;
			//std::cout << "\n";
		}
	}

	void PhysicsEngine::ApplyGravity(RigidBody& rb) {
		rb.AddForce(rb.Gravity * rb.Mass * PhysicsEngine::_fixTimeStep);
	}
	void PhysicsEngine::ApplyBaseFriction(RigidBody& rb) {
		//Vector3 quadSpeed = rb._velocity * rb._velocity;
		//Vector3 resistForce = quadSpeed * 0.5 * 5.29 * 1 * 1;
		//rb.AddForce(resistForce);
		//rb._force *= rb.BaseFriction;
		//rb._force *= rb.BaseFriction;
		rb._velocity *= rb.BaseFriction;
	}

	void PhysicsEngine::ApplyTorque(RigidBody& rb) {
		//Recalculate angular velocity
		//Eigen::Matrix3f inverseMatrix;
		//if (MatrixMath::GetInverseMatrix3x3(rb._inertiaMatrix, inverseMatrix) == false)
			//return;

		//MatrixMath::MultiplyMatrix(rb._angularVelocity, rb._angularMomentum, inverseMatrix);

		//float angle = Vector3::GetAngle(rb.);
	}

	void PhysicsEngine::Contact(RigidBody& rb1, glm::vec3 contactNormal) {
		contactNormal = glm::normalize(contactNormal);
		//Math::RemoveError(contactNormal);

		float u1 = glm::dot(rb1._velocity, contactNormal);
		glm::vec3 newVelocity = rb1._velocity + contactNormal * (2 * 1 * (0 - u1) / (rb1.Mass + 0)) * rb1.ElasticityCoefficient;

		rb1._velocity = newVelocity;

		//Calculate torque
		glm::vec3 contactPoint;


		std::cout << Core::World::GetElapsedTime() << " contact " << contactNormal.y << "\n";
	}
	void PhysicsEngine::Contact(RigidBody& rb1, RigidBody& rb2, glm::vec3 contactNormal) {
		contactNormal = glm::normalize(contactNormal);
		//Math::RemoveError(contactNormal);

		float u1 = glm::dot(rb1._velocity, -contactNormal);
		float u2 = glm::dot(rb2._velocity, contactNormal);

		glm::vec3 newRb1Vector = rb1._velocity + contactNormal * (2 * rb2.Mass * (u2 - u1) / (rb1.Mass + rb2.Mass)) * rb1.ElasticityCoefficient;
		glm::vec3 newRb2Vector = rb2._velocity + contactNormal * (2 * rb1.Mass * (u1 - u2) / (rb2.Mass + rb1.Mass)) * rb2.ElasticityCoefficient;

		rb1._velocity = newRb1Vector;
		rb1._velocity = newRb2Vector;
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

			std::cout << rb._force.y << " xForce\n";

			glm::vec3 newVelocity = rb.GetVelocity() + rb._force / rb.Mass;

			if (glm::length(newVelocity) > rb.MaxSpeed) {
				rb._velocity = glm::normalize(newVelocity) * rb.MaxSpeed;
				rb.GetParentObject()->transform.AddPosition(rb.GetVelocity() * PhysicsEngine::_fixTimeStep);
			}
			else
			{
				rb._velocity = newVelocity;
				rb.GetParentObject()->transform.AddPosition(rb.GetVelocity() * PhysicsEngine::_fixTimeStep);
			}

			accumulator -= PhysicsEngine::_fixTimeStep;
			rb._force = { 0,0,0 };
		}

		if (accumulator != 0) {
			const double alpha = accumulator / PhysicsEngine::_fixTimeStep;

			PhysicsEngine::ApplyGravity(rb);
			PhysicsEngine::ApplyBaseFriction(rb);

			glm::vec3 newVelocity = rb.GetVelocity() + rb._force / rb.Mass;

			std::cout << newVelocity.x << " xForce\t" << newVelocity.y << " yForce\n";

			if (glm::length(newVelocity) > rb.MaxSpeed) {
				rb._velocity = glm::normalize(newVelocity) * rb.MaxSpeed;

				glm::vec3 magnitude(PhysicsEngine::_fixTimeStep * alpha, PhysicsEngine::_fixTimeStep * alpha, PhysicsEngine::_fixTimeStep * alpha);
				rb.GetParentObject()->transform.AddPosition(rb.GetVelocity() * magnitude);
			}
			else
			{
				rb._velocity += (newVelocity - rb._velocity) * glm::vec3(alpha);
				//rb.GetParentObject()->AddPosition();
				glm::vec3 newPos = rb.GetParentObject()->transform.GetPosition() + (rb.GetVelocity() * PhysicsEngine::_fixTimeStep);
				rb.GetParentObject()->transform.AddPosition((newPos - rb.GetParentObject()->transform.GetPosition()) * glm::vec3(alpha));
			}
		}

		//std::cout << rb.GetParentObject()->GetPosition().Y << " YPos\t" << rb._velocity.Y << " speed\t" << rb._force.Y << " force\t" << World::GetDeltaTime() << " DeltaTime\t" << World::GetTimeLong() << " \TimeLong" << "\n";

		rb._force = { 0,0,0 };
		//std::cout << World::GetTimeLong() << " worldTime\n";
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
		state.Velocity = rb._velocity;

		while (accumulator >= PhysicsEngine::_fixTimeStep)
		{
			state.Position = rb.GetParentObject()->transform.GetPosition();
			state.Velocity = rb._velocity;

			PhysicsEngine::ApplyGravity(rb);
			PhysicsEngine::ApplyBaseFriction(rb);

			integrate(state, PhysicsEngine::_fixTimeStep, rb._force, rb.Mass);

			rb._velocity = state.Velocity;
			rb.GetParentObject()->transform.SetPosition(state.Position);

			std::cout << state.Velocity.y << " speed\t" << rb._force.y << " force\t" << "\n";

			accumulator -= PhysicsEngine::_fixTimeStep;
			rb._force = { 0,0,0 };
		}
		if (accumulator != 0) {
			const double alpha = accumulator / PhysicsEngine::_fixTimeStep;

			state.Position = rb.GetParentObject()->transform.GetPosition();
			state.Velocity = rb._velocity;

			PhysicsEngine::ApplyGravity(rb);
			PhysicsEngine::ApplyBaseFriction(rb);

			integrate(state, PhysicsEngine::_fixTimeStep, rb._force, rb.Mass);

			rb._velocity += (state.Velocity - rb._velocity) * glm::vec3(alpha);
			rb.GetParentObject()->transform.AddPosition(state.Velocity * PhysicsEngine::_fixTimeStep * glm::vec3(alpha));

			std::cout << state.Velocity.y << " speed\t" << rb._force.y << " force\t" << "\n";
		}

		rb._force = { 0,0,0 };
		std::cout << Core::World::GetElapsedTime() << " worldTime\n";
	}
}