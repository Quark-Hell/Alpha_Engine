#include "Object.h"

#include "Factory.h"
#include "Components/Component.h"

#include "Logger/Logger.h"

#define M_PI 3.14159265358979323846

Core::Object::Object() = default;
Core::Object::~Object() = default;

void Core::Object::Delete() {
	Object::~Object();
}

void Core::Object::SetName(const std::string &newName) {
	_name = newName;
}
std::string Core::Object::GetName() {
	return _name;
}

bool Core::Object::AddComponent(Component& component) {
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
	Logger::Logger::LogInfo("Component attached successfully");
	return true;
}

size_t Core::Object::GetCountOfComponents() const {
	return Object::_components.size();
}

glm::mat4x4 Core::Object::GetTransformMatrix() {
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

