#include "Rigidbody.h"
#include <memory>

#include "AxisEngine/Components/Collider.h"
#include "Core/Object.h"

namespace AxisEngine {
	RigidBody::RigidBody() {

	}

	void RigidBody::UpdateParentObject() {
		RigidBody::CalculateCenterMass();

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

	void RigidBody::CalculateCenterMass() {
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

		//for (unsigned int it = 0; it < colliders.size(); it++) {
		//	for (unsigned int jt = 0; jt < colliders[it]._vertex->size(); jt += 3) {
		//		//X
		//		if ((*colliders[it]._vertex)[jt] < scope[0]) {
		//			scope[0] = (*colliders[it]._vertex)[jt];
		//		}
		//		else if ((*colliders[it]._vertex)[jt] > scope[1]) {
		//			scope[1] = (*colliders[it]._vertex)[jt];
		//		}
		//
		//		//Y
		//		if ((*colliders[it]._vertex)[jt + 1] < scope[2]) {
		//			scope[2] = (*colliders[it]._vertex)[jt + 1];
		//		}
		//		else if ((*colliders[it]._vertex)[jt + 1] > scope[3]) {
		//			scope[3] = (*colliders[it]._vertex)[jt + 1];
		//		}
		//
		//		//Z
		//		if ((*colliders[it]._vertex)[jt + 2] < scope[4]) {
		//			scope[4] = (*colliders[it]._vertex)[jt + 2];
		//		}
		//		else if ((*colliders[it]._vertex)[jt + 2] > scope[5]) {
		//			scope[5] = (*colliders[it]._vertex)[jt + 2];
		//		}
		//	}
		//
		//	float xScope = scope[1] - scope[0];
		//	float yScope = scope[3] - scope[2];
		//	float zScope = scope[5] - scope[4];
		//
		//	RigidBody::_centerMass += glm::vec3(xScope, yScope, zScope) / glm::vec3(2, 2, 2);
		//}

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