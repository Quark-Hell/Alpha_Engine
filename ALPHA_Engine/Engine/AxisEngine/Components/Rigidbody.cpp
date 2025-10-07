#include "Rigidbody.h"
#include <memory>

#include "AxisEngine/Components/Collider.h"
#include "Core/Logger/Logger.h"
#include "Core/Objects/Object.h"
#include "Core/Objects/GameObject.h"

namespace AxisEngine {
	RigidBody::RigidBody() {

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
		RigidBody::UpdateCenterMass();

		RigidBody::_velocity = { 0,0,0 };
		//RigidBody::ResetInertiaMatrix();
	}

	void RigidBody::AddForce(const glm::vec3& forceVector) {
		RigidBody::_force += forceVector;
	}
	void RigidBody::AddForce(const float& x, const float& y, const float& z) {
		RigidBody::_force += glm::vec3(x, y, z);
	}

	void RigidBody::AddAngularMomentum(const glm::vec3& forceVector, glm::vec3 relativePoint) {
		RigidBody::_angularMomentum += forceVector * (relativePoint - RigidBody::_centerMass);
	}
	void RigidBody::AddAngularMomentum(const float& x, const float& y, const float& z, glm::vec3 relativePoint) {
		RigidBody::_angularMomentum += glm::vec3(x, y, z) * (relativePoint - RigidBody::_centerMass);
	}

	void RigidBody::UpdateCenterMass() {
		RigidBody::_centerMass = glm::vec3(0, 0, 0);

		auto colliders = GetParentObject()->GetComponentsByType<Collider>();

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

		for (auto& colliderRef : colliders)
		{
			const auto& collider = colliderRef.get();
			const auto& vertices = *collider.GetVertices();

			for (size_t jt = 0; jt < vertices.size(); jt += 3)
			{
				// X
				if (vertices[jt] < scope[0])
					scope[0] = vertices[jt];
				else if (vertices[jt] > scope[1])
					scope[1] = vertices[jt];

				// Y
				if (vertices[jt + 1] < scope[2])
					scope[2] = vertices[jt + 1];
				else if (vertices[jt + 1] > scope[3])
					scope[3] = vertices[jt + 1];

				// Z
				if (vertices[jt + 2] < scope[4])
					scope[4] = vertices[jt + 2];
				else if (vertices[jt + 2] > scope[5])
					scope[5] = vertices[jt + 2];
			}

			//set all scopes to zero if collider hasn't vertices
			for (int i = 0; i < 6; ++i) {
				if (scope[i] == FLT_MAX || scope[i] == -FLT_MAX)
					scope[i] = 0.0f;
			}

			float xScope = scope[1] - scope[0];
			float yScope = scope[3] - scope[2];
			float zScope = scope[5] - scope[4];

			RigidBody::_centerMass += glm::vec3(xScope, yScope, zScope) / glm::vec3(2, 2, 2);
		}

		RigidBody::_centerMass /= colliders.size();
	}
	glm::vec3 RigidBody::GetCenterMass() {
		return RigidBody::_centerMass;
	}

	glm::vec3 RigidBody::GetVelocity() {
		return RigidBody::_velocity;
	}

	bool RigidBody::GetContactPoints(std::vector<glm::vec3>& contactPoint) {
		if (!RigidBody::_hasCollision)
			return false;

		contactPoint = { _contactPoints.begin(), _contactPoints.end() };
		return true;
	}

	void RigidBody::AddContactPoints(std::vector<glm::vec3>& points) {
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

		glm::vec3 realPullingVector;
		for (size_t i = 0; i < _pullingVectors.size(); i++)
		{
			//RigidBody::GetParentObject()->AddPosition(_pullingVectors[i]);
			realPullingVector += _pullingVectors[i];
		}
		realPullingVector /= _pullingVectors.size();

		GetParentObject()->transform.AddPosition(realPullingVector);
	}

	void RigidBody::Contact(RigidBody& rb1, glm::vec3 contactNormal) {
		contactNormal = glm::normalize(contactNormal);
		//Math::RemoveError(contactNormal);

		float u1 = glm::dot(rb1._velocity, contactNormal);
		glm::vec3 newVelocity = rb1._velocity + contactNormal * (2 * 1 * (0 - u1) / (rb1.Mass + 0)) * rb1.ElasticityCoefficient;

		rb1._velocity = newVelocity;
	}
	void RigidBody::Contact(RigidBody& rb1, RigidBody& rb2, glm::vec3 contactNormal) {
		contactNormal = glm::normalize(contactNormal);
		//Math::RemoveError(contactNormal);

		float u1 = glm::dot(rb1._velocity, -contactNormal);
		float u2 = glm::dot(rb2._velocity, contactNormal);

		glm::vec3 newRb1Vector = rb1._velocity + contactNormal * (2 * rb2.Mass * (u2 - u1) / (rb1.Mass + rb2.Mass)) * rb1.ElasticityCoefficient;
		glm::vec3 newRb2Vector = rb2._velocity + contactNormal * (2 * rb1.Mass * (u1 - u2) / (rb2.Mass + rb1.Mass)) * rb2.ElasticityCoefficient;

		rb1._velocity = newRb1Vector;
		rb1._velocity = newRb2Vector;
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
}