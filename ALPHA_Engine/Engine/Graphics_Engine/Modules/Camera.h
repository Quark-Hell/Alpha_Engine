#pragma once
class Vector3;

#include "Core/Components/Component.h"
#include "Core/Components/Transform.h"

#include "glm.hpp"


namespace Core {
	class Object;
}

namespace GraphicsEngine {

	enum ProjectionMode {
		Perspective = 0,
		Orthographic = 1,
	};

	class Camera : public Core::Component {
	private:
		Core::Transform _transform;

		float Fov = 90;
		float Aspect = 1;
		float ZNear = 0.1f;
		float ZFar = 300;

		//TODO: Add function for change mode
		ProjectionMode _projectionMode = ProjectionMode::Perspective;

		glm::mat4x4 _projectionMatrix = glm::mat4x4(1.0f);

	protected:
		Camera();

	public:

		~Camera();

		void SetCameraInfo(float Fov, float Aspect, float ZNear, float ZFar);
		void GetCameraInfo(float* Fov, float* Aspect, float* ZNear, float* ZFar);

		void SetParentObject(const Core::Object& parent) override;

		float GetFov();
		float GetAspect();
		float GetZNear();
		float GetZFar();

		glm::mat4x4 GetProjectionMatrix();
		glm::mat4x4 GetTransformMatrix();

		void UpdateProjectionMatrix();
		void UpdateViewMatrix();
	};

}