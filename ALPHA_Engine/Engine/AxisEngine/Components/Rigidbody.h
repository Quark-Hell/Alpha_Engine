#pragma once

#include <vector>

#include "Core/Components/Component.h"
#include "glm/glm.hpp"

namespace Core {
	class Object;
}

namespace AxisEngine {
	class RigidBody final : public Core::Component {
		friend class PhysicsEngine;
		friend class CollisionEngine;

		friend class RigidBodiesBuffer;

	public:
		float Mass = 1;
		glm::vec3 Gravity = glm::vec3{ 0,-9.81,0 };
		float BaseFriction = 0.995;
		/*Description:
		if = 1 than body movement reflect
		if = 0 than body stop*/
		float ElasticityCoefficient = 0.7f;
		float FrictionCoefficient = 0.3f;
		float MaxSpeed = 2000;

	private:
		glm::vec3 _force{ 0,0,0 };
		//Vector3 _acceleration{ 0,0,0 };
		glm::vec3 _velocity{ 0,0,0 };

		glm::vec3 _centerMass;

		glm::vec3 _rotationVector{ 0,0,0 };
		glm::vec4 _orientation{ 0,0,0,0 };
		glm::vec3 _angularMomentum{ 0,0,0 };
		glm::vec3 _angularVelocity{ 0,0,0 };

		std::vector<glm::vec3> _contactPoints;
		std::vector<glm::vec3> _pullingVectors;

		bool _hasCollision = false;
		//Matrix3x3 _inertiaMatrix;

	private:
		RigidBody();
		bool CheckAddPossibility(Core::Object& newParent) override;
		void UpdateParentObject(Core::Object& newParent) override;

		static void Contact(RigidBody& rb1, glm::vec3 contactNormal);
		static void Contact(RigidBody& rb1, RigidBody& rb2, glm::vec3 contactNormal);

	public:
        ~RigidBody() override = default;

		void AddForce(const glm::vec3& forceVector);
		void AddForce(const float& x, const float& y, const float& z);

		void AddAngularMomentum(const glm::vec3& forceVector, glm::vec3 relativePoint);
		void AddAngularMomentum(const float& x, const float& y, const float& z, glm::vec3 relativePoint);

		void UpdateCenterMass();
		[[nodiscard]] glm::vec3 GetCenterMass();

		[[nodiscard]] glm::vec3 GetVelocity();
		[[nodiscard]] glm::vec3 GetPosition();

		[[nodiscard]] bool GetContactPoints(std::vector<glm::vec3>& contactPoint);

		void AddContactPoints(std::vector<glm::vec3>& points);

		void ClearCollisinInfo();

		void ApplyPullingVectors();

		void SetInertiaMatrix(glm::mat3x3 matrix);
		void ResetInertiaMatrix();
		glm::mat3x3 GetInertiaMatrix();
	};
}

