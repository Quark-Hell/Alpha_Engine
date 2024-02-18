#include "Physics.h"

#include "Modules/Module.h"

#include "Basical_Type.h"
#include "Geometry.h"
#include "World.h"

#pragma region RigidBody definee
Object* RigidBody::GetParentObject() {
	return Module::GetParentObject();
}
void RigidBody::SetParentObject(const Object& parent) {
	RigidBody::ParentObject = const_cast<Object*>(&parent);
	RigidBody::CalculateCenterMass();

	RigidBody::_velocity = { 0,0,0 };
	//RigidBody::ResetInertiaMatrix();
}

void RigidBody::AddForce(const Vector3& forceVector) {
	RigidBody::_force += forceVector;
}
void RigidBody::AddForce(const float& x, const float& y, const float& z) {
	RigidBody::_force += Vector3(x, y, z);
}

void RigidBody::AddAngularMomentum(const Vector3& forceVector, Vector3 relativePoint) {
	RigidBody::_angularMomentum += forceVector * (relativePoint - RigidBody::_centerMass);
}
void RigidBody::AddAngularMomentum(const float& x, const float& y, const float& z, Vector3 relativePoint) {
	RigidBody::_angularMomentum += Vector3(x, y, z) * (relativePoint - RigidBody::_centerMass);
}

ModulesList RigidBody::GetType() {
	return ModulesList::RigidBodyType;
}

void RigidBody::CalculateCenterMass() {
	Object* object = RigidBody::GetParentObject();
	RigidBody::_centerMass = Vector3(0, 0, 0);
	std::vector<std::shared_ptr<Geometry>> geometries;

	for (size_t i = 0; i < object->GetCountOfModules(); i++)
	{
		std::shared_ptr<Geometry> geometry = std::dynamic_pointer_cast<Geometry>(object->GetModuleByIndex(i));
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
		for (unsigned int jt = 0; jt < geometries[it]->_vertex->size(); jt += 3) {
			//X
			if ((*geometries[it]->_vertex)[jt] < scope[0]) {
				scope[0] = (*geometries[it]->_vertex)[jt];
			}
			else if ((*geometries[it]->_vertex)[jt] > scope[1]) {
				scope[1] = (*geometries[it]->_vertex)[jt];
			}

			//Y
			if ((*geometries[it]->_vertex)[jt + 1] < scope[2]) {
				scope[2] = (*geometries[it]->_vertex)[jt + 1];
			}
			else if ((*geometries[it]->_vertex)[jt + 1] > scope[3]) {
				scope[3] = (*geometries[it]->_vertex)[jt + 1];
			}

			//Z
			if ((*geometries[it]->_vertex)[jt + 2] < scope[4]) {
				scope[4] = (*geometries[it]->_vertex)[jt + 2];
			}
			else if ((*geometries[it]->_vertex)[jt + 2] > scope[5]) {
				scope[5] = (*geometries[it]->_vertex)[jt + 2];
			}
		}

		float xScope = scope[1] - scope[0];
		float yScope = scope[3] - scope[2];
		float zScope = scope[5] - scope[4];

		RigidBody::_centerMass += Vector3(xScope, yScope, zScope) / 2;
	}

	RigidBody::_centerMass /= geometries.size();
}
Vector3 RigidBody::GetCenterMass() {
	return RigidBody::_centerMass;
}

Vector3 RigidBody::GetVelocity() {
	return RigidBody::_velocity;
}
Vector3 RigidBody::GetPosition() {
	return RigidBody::GetParentObject()->GetPosition();
}

bool RigidBody::GetContactPoints(std::vector<Vector3>& contactPoint) {
	if (!RigidBody::_hasCollision)
		return false;

	contactPoint = { _contactPoints.begin(), _contactPoints.end() };
	return true;
}

void RigidBody::AddContactPoints(std::vector<Vector3>& points) {
	for (size_t i = 0; i < points.size(); i++) {
		RigidBody::_contactPoints.push_back(points[i]);
	}
}

void RigidBody::ClearCollisinInfo() {
	RigidBody::_hasCollision = false;
	RigidBody::_contactPoints.clear();
	RigidBody::_pullingVectors.clear();
}

void RigidBody::ApplyPullingVectors() {
	if (_pullingVectors.size() == 0)
		return;

	std::cout << _pullingVectors.size() << " pVectorSize\n";

	Vector3 realPullingVector;
	for (size_t i = 0; i < _pullingVectors.size(); i++)
	{
		//RigidBody::GetParentObject()->AddPosition(_pullingVectors[i]);
		realPullingVector += _pullingVectors[i];
	}
	realPullingVector /= _pullingVectors.size();

	RigidBody::GetParentObject()->AddPosition(realPullingVector);
}

//void RigidBody::SetInertiaMatrix(Matrix3x3 matrix) {
//	RigidBody::_inertiaMatrix = matrix;
//}
//void RigidBody::ResetInertiaMatrix() {
//	RigidBody::_inertiaMatrix.Identity();
//}
//Matrix3x3 RigidBody::GetInertiaMatrix() {
//	return RigidBody::_inertiaMatrix;
//}


RigidBody::RigidBody() {

}
RigidBody::~RigidBody() {

}
#pragma endregion

#pragma region Phisycs Define
void Physics::PullingVectorsLoop() {
	for (size_t it = 0; it < World::ObjectsOnScene.size(); it++)
	{
		Object* obj = World::ObjectsOnScene[it];
		std::shared_ptr<RigidBody> rigidBody = std::dynamic_pointer_cast<RigidBody>(obj->GetModuleByType(RigidBodyType));

		if (rigidBody == nullptr)
			continue;

		//Physics::ApplyBaseFriction(*rigidBody);
		rigidBody->ApplyPullingVectors();

		//std::cout << rigidBody->_movementVector.X;
		//std::cout << "\n";
	}
}

void Physics::PhysicsLoop() {

	for (size_t it = 0; it < World::ObjectsOnScene.size(); it++)
	{
		Object* obj = World::ObjectsOnScene[it];
		std::shared_ptr<RigidBody> rigidBody = std::dynamic_pointer_cast<RigidBody>(obj->GetModuleByType(RigidBodyType));

		if (rigidBody == nullptr)
			continue;

		Physics::ApplyPhysics(*rigidBody);

		//std::cout << rigidBody->_movementVector.X;
		//std::cout << "\n";
	}
}

void Physics::ApplyGravity(RigidBody& rb) {
	rb.AddForce(rb.Gravity * rb.Mass * Physics::fixTimeStep);
}
void Physics::ApplyBaseFriction(RigidBody& rb) {
	//Vector3 quadSpeed = rb._velocity * rb._velocity;
	//Vector3 resistForce = quadSpeed * 0.5 * 5.29 * 1 * 1;
	//rb.AddForce(resistForce);
	//rb._force *= rb.BaseFriction;
	//rb._force *= rb.BaseFriction;
	rb._velocity *= rb.BaseFriction;
}

void Physics::ApplyTorque(RigidBody& rb) {
	//Recalculate angular velocity
	//Eigen::Matrix3f inverseMatrix;
	//if (MatrixMath::GetInverseMatrix3x3(rb._inertiaMatrix, inverseMatrix) == false)
		//return;

	//MatrixMath::MultiplyMatrix(rb._angularVelocity, rb._angularMomentum, inverseMatrix);

	//float angle = Vector3::GetAngle(rb.);
}

void Physics::Contact(RigidBody& rb1, Vector3 contactNormal) {
	contactNormal.NormilizeSelf();
	Math::RemoveError(contactNormal);
	
	float u1 = Vector3::DotProduct(rb1._velocity, contactNormal);
	Vector3 newVelocity = rb1._velocity + contactNormal * (2 * 1 * (0 - u1) / (rb1.Mass + 0)) * rb1.ElasticityCoefficient;
	
	rb1._velocity = newVelocity;

	//Calculate torque
	Vector3 contactPoint;
	

	std::cout << World::GetTimeLong() << " contact " << contactNormal.Y << "\n";
}
void Physics::Contact(RigidBody& rb1, RigidBody& rb2, Vector3 contactNormal) {
	contactNormal.NormilizeSelf();
	Math::RemoveError(contactNormal);
	
	float u1 = Vector3::DotProduct(rb1._velocity, -contactNormal);
	float u2 = Vector3::DotProduct(rb2._velocity, contactNormal);
	
	Vector3 newRb1Vector = rb1._velocity + contactNormal * (2 * rb2.Mass * (u2 - u1) / (rb1.Mass + rb2.Mass)) * rb1.ElasticityCoefficient;
	Vector3 newRb2Vector = rb2._velocity + contactNormal * (2 * rb1.Mass * (u1 - u2) / (rb2.Mass + rb1.Mass)) * rb2.ElasticityCoefficient;

	rb1._velocity = newRb1Vector;
	rb1._velocity = newRb2Vector;
}


void Physics::ApplyPhysics(RigidBody& rb) {
	switch (Physics::IntegrateMethod)
	{
	case SemiImplicitEuler:
		Physics::SemiImplicitIntegrate(rb);
		break;
	case RK4:
		Physics::RK4Integrate(rb);
		break;
	default:
		break;
	}
}

void Physics::SemiImplicitIntegrate(RigidBody& rb) {
	double accumulator = World::GetDeltaTime();
	if (accumulator > _maxTimeStep)
		accumulator = Physics::fixTimeStep;

	while (accumulator >= Physics::fixTimeStep)
	{
		Physics::ApplyGravity(rb);
		Physics::ApplyBaseFriction(rb);

		std::cout << rb._force.Y << " xForce\n";

		Vector3 newVelocity = rb.GetVelocity() + rb._force / rb.Mass;

		if (newVelocity > rb.MaxSpeed) {
			rb._velocity = Vector3::GetNormalize(newVelocity) * rb.MaxSpeed;
			rb.GetParentObject()->AddPosition(rb.GetVelocity() * Physics::fixTimeStep);
		}
		else
		{
			rb._velocity = newVelocity;
			rb.GetParentObject()->AddPosition(rb.GetVelocity() * Physics::fixTimeStep);
		}

		accumulator -= Physics::fixTimeStep;
		rb._force = { 0,0,0 };
	}

	if (accumulator != 0) {
		const double alpha = accumulator / Physics::fixTimeStep;
		
		Physics::ApplyGravity(rb);
		Physics::ApplyBaseFriction(rb);
		
		Vector3 newVelocity = rb.GetVelocity() + rb._force / rb.Mass;

		std::cout << newVelocity.X << " xForce\t" << newVelocity.Y << " yForce\n";

		if (newVelocity > rb.MaxSpeed) {
			rb._velocity = Vector3::GetNormalize(newVelocity) * rb.MaxSpeed;
			rb.GetParentObject()->AddPosition(rb.GetVelocity() * Physics::fixTimeStep * alpha);
		}
		else
		{
			rb._velocity += (newVelocity - rb._velocity) * alpha;
			//rb.GetParentObject()->AddPosition();
			Vector3 newPos = rb.GetParentObject()->GetPosition() + (rb.GetVelocity() * Physics::fixTimeStep);
			rb.GetParentObject()->AddPosition((newPos - rb.GetParentObject()->GetPosition()) * alpha);
		}
	}

	//std::cout << rb.GetParentObject()->GetPosition().Y << " YPos\t" << rb._velocity.Y << " speed\t" << rb._force.Y << " force\t" << World::GetDeltaTime() << " DeltaTime\t" << World::GetTimeLong() << " \TimeLong" << "\n";

	rb._force = { 0,0,0 };
	//std::cout << World::GetTimeLong() << " worldTime\n";
}

void Physics::RK4Integrate(RigidBody& rb) {
	auto evaluate = [](const State& initial, float dt, const Derivative& d, Vector3 force, float mass) {
		State state;
		state.Position = initial.Position + d.dx * dt;
		state.Velocity = initial.Velocity + d.dv;

		Derivative output;
		output.dx = state.Velocity;
		output.dv = force / mass;
		return output;
	};

	auto integrate = [evaluate](State& state, float dt, Vector3 force, float mass)
	{
		Derivative a, b, c, d;

		a = evaluate(state, 0.0f, Derivative(), force, mass);
		b = evaluate(state, dt * 0.5f, a, force, mass);
		c = evaluate(state, dt * 0.5f, b, force, mass);
		d = evaluate(state, dt, c, force, mass);

		Vector3 dxdt = (a.dx + (b.dx + c.dx) * 2.0f + d.dx) * (1.0f / 6.0f);
		Vector3 dvdt = (a.dv + (b.dv + c.dv) * 2.0f + d.dv) * (1.0f / 6.0f);

		state.Position = state.Position + dxdt * dt;
		state.Velocity = state.Velocity + dvdt;
	};

	double accumulator = World::GetDeltaTime();

	State state;
	state.Position = rb.GetParentObject()->GetPosition();
	state.Velocity = rb._velocity;

	while (accumulator >= Physics::fixTimeStep)
	{
		state.Position = rb.GetParentObject()->GetPosition();
		state.Velocity = rb._velocity;

		Physics::ApplyGravity(rb);
		Physics::ApplyBaseFriction(rb);

		integrate(state, Physics::fixTimeStep, rb._force, rb.Mass);
		
		rb._velocity = state.Velocity;
		rb.GetParentObject()->SetPosition(state.Position);

		std::cout << state.Velocity.Y << " speed\t" << rb._force.Y << " force\t" << "\n";

		accumulator -= Physics::fixTimeStep;
		rb._force = { 0,0,0 };
	}
	if (accumulator != 0) {
		const double alpha = accumulator / Physics::fixTimeStep;
		
		state.Position = rb.GetParentObject()->GetPosition();
		state.Velocity = rb._velocity;
		
		Physics::ApplyGravity(rb);
		Physics::ApplyBaseFriction(rb);

		integrate(state, Physics::fixTimeStep, rb._force, rb.Mass);
		
		rb._velocity += (state.Velocity - rb._velocity) * alpha;
		rb.GetParentObject()->AddPosition(state.Velocity * Physics::fixTimeStep * alpha);

		std::cout << state.Velocity.Y << " speed\t" << rb._force.Y << " force\t" << "\n";
	}

	rb._force = { 0,0,0 };
	std::cout << World::GetTimeLong() << " worldTime\n";
}

Physics::Physics() {

}
Physics::~Physics() {

}