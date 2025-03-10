#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Core/Math/Vectors.h"

namespace Core {

	class Transform {
	private:
        glm::vec3 _position{0,0,0};
		glm::vec4 _rotation{0,0,0,1};
		glm::vec3 _scale{1,1,1};

		glm::mat4x4 _transformMatrix{1};

	public:
		Transform();
		~Transform() = default;

        [[nodiscard]] glm::vec3 GetPosition();
		void AddPosition(float X, float Y, float Z);
		void AddPosition(const glm::vec3& position);

		void SetPosition(float X, float Y, float Z);
		void SetPosition(const glm::vec3& position);


        [[nodiscard]] glm::vec4 GetRotation();
		void AddRotation(float X, float Y, float Z);
		void AddRotation(glm::vec3 rotation);

		void SetRotation(float X, float Y, float Z);
		void SetRotation(glm::vec3 rotation);


        [[nodiscard]] glm::vec3 GetScale();
        void SetScale(float X, float Y, float Z);
		void SetScale(glm::vec3 scale);

		glm::mat4x4 GetTransformMatrix();
	};

}
