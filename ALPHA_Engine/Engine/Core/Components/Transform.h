#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Core/Math/glmMath.h"

namespace Core {
	class Transform {
	private:
		glm::vec3 _position{ 0,0,0 };
		glm::vec4 _rotation{ 0,0,0,1 };
		glm::vec3 _scale{ 1,1,1 };

		glm::mat4x4 _transformMatrix{ 1 };

	public:
		Transform();
		~Transform() = default;

		/**
		 * @brief Gets the current world position of the object.
		 * @return The position as a glm::vec3.
		 */
		[[nodiscard]] glm::vec3 GetPosition();
		/**
		 * @brief Adds a delta to the current position.
		 * @param X Delta along the X-axis.
		 * @param Y Delta along the Y-axis.
		 * @param Z Delta along the Z-axis.
		 */
		void AddPosition(float X, float Y, float Z);
		/**
		 * @brief Adds a delta to the current position.
		 * @param position Delta vector to add.
		 */
		void AddPosition(const glm::vec3& position);


		/**
		 * @brief Sets the absolute position of the object.
		 * @param X New X coordinate.
		 * @param Y New Y coordinate.
		 * @param Z New Z coordinate.
		 */
		void SetPosition(float X, float Y, float Z);
		/**
		 * @brief Sets the absolute position of the object.
		 * @param position New position vector.
		 */
		void SetPosition(const glm::vec3& position);


		/**
		 * @brief Gets the current rotation of the object.
		 * @return Rotation as a glm::vec4 (e.g., quaternion or axis-angle).
		 */
		[[nodiscard]] glm::vec4 GetRotation();
		/**
		 * @brief Adds a delta rotation to the current rotation.
		 * @param X Rotation delta along the X-axis (degrees or radians depending on convention).
		 * @param Y Rotation delta along the Y-axis.
		 * @param Z Rotation delta along the Z-axis.
		 */
		void AddRotation(float X, float Y, float Z);
		/**
		 * @brief Adds a delta rotation to the current rotation.
		 * @param rotation Rotation delta vector.
		 */
		void AddRotation(glm::vec3 rotation);

		/**
		 * @brief Sets the absolute rotation of the object.
		 * @param X New rotation along the X-axis.
		 * @param Y New rotation along the Y-axis.
		 * @param Z New rotation along the Z-axis.
		 */
		void SetRotation(float X, float Y, float Z);
		/**
		 * @brief Sets the absolute rotation of the object.
		 * @param rotation New rotation vector.
		 */
		void SetRotation(glm::vec3 rotation);

		/**
		 * @brief Gets the current scale of the object.
		 * @return Scale as a glm::vec3.
		 */
		[[nodiscard]] glm::vec3 GetScale();
		/**
		 * @brief Sets the absolute scale of the object.
		 * @param X Scale factor along the X-axis.
		 * @param Y Scale factor along the Y-axis.
		 * @param Z Scale factor along the Z-axis.
		 */
		void SetScale(float X, float Y, float Z);
		/**
		 * @brief Sets the absolute scale of the object.
		 * @param scale New scale vector.
		 */
		void SetScale(glm::vec3 scale);

		/**
		 * @brief Returns the object's transform matrix.
		 * @return 4x4 transformation matrix combining position, rotation, and scale.
		 */
		glm::mat4x4 GetTransformMatrix();
	};
}
