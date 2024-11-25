#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/transform.hpp>
#include "glm/gtx/string_cast.hpp"

#include "Core/Math/Vectors.h"

namespace Core {

	class Transform {
	private:
		Vector3 _position{0,0,0};
		Vector4 _rotation{0,0,0};
		Vector3 _scale{1,1,1};

		Vector3 _origin{ 0,0,0 };

		glm::mat4x4 _transformMatrix{1};

	public:
		Transform();
		~Transform() = default;

		Vector3 GetPosition();
		void AddPosition(float X, float Y, float Z);
		void AddPosition(const Vector3& position);

		void SetPosition(float X, float Y, float Z);
		void SetPosition(const Vector3& position);


		Vector4 GetRotation();
		void AddRotation(float X, float Y, float Z);
		void AddRotation(Vector3 rotation);

		void SetRotation(float X, float Y, float Z);
		void SetRotation(Vector3 rotation);


		Vector3 GetScale();
		void SetScale(float X, float Y, float Z);
		void SetScale(Vector3 scale);

		void AddOriginPosition(float X, float Y, float Z);
		void AddOriginPosition(const Vector3& position);

		void SetOriginPosition(float X, float Y, float Z);
		void SetOriginPosition(const Vector3 &position);

		glm::mat4x4 GetTransformMatrix();
	};

}
