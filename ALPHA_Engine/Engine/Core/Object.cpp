#include "Object.h"

#include "Factory.h"
#include "Components/Component.h"

#include "Logger/Logger.h"

#define M_PI 3.14159265358979323846

namespace Core {
	Object::Object() = default;
	Object::~Object() = default;

	void Object::Delete() {
		Object::~Object();
	}

	void Object::SetName(const std::string& newName) {
		_name = newName;
	}
	std::string Object::GetName() {
		return _name;
	}

	bool Object::AddComponent(Component& component) {
		// Check if component is already added
		for (auto* c : _components) {
			if (c == &component) {
				Logger::Logger::LogError("Component already attached");
				return false;  // do not add again
			}
		}

		// Add component
		_components.push_back(&component);
		component.ParentObject = this;
		component.UpdateParentObject();
		Logger::Logger::LogInfo("Component attached successfully");
		return true;
	}

	size_t Object::GetCountOfComponents() const {
		return Object::_components.size();
	}

	glm::mat4x4 Object::GetTransformMatrix() {
		glm::mat4x4 rotMat(1.0f);
		const glm::vec4 rot = transform.GetRotation();

		const float radX = M_PI / 180 * rot.x;
		const float radY = M_PI / 180 * rot.y;
		const float radZ = M_PI / 180 * rot.z;

		rotMat = glm::rotate(rotMat, radX, glm::vec3(1.0f, 0.0f, 0.0f));
		rotMat = glm::rotate(rotMat, radY, glm::vec3(0.0f, 1.0f, 0.0f));
		rotMat = glm::rotate(rotMat, radZ, glm::vec3(0.0f, 0.0f, 1.0f));

		const glm::mat4x4 transMat = glm::translate(transform.GetPosition());

		const glm::mat4x4 transformMatrix = rotMat * transMat;

		return transformMatrix;
	}

	const Component& Object::GetComponentByIndex(size_t index) const {
		if (index >= _components.size())
		{
			Logger::Logger::LogError(
				"Component index out of range " + std::string(__FILE__ ":") + std::to_string(__LINE__)
			);
		}

		return *_components[index];
	}
}