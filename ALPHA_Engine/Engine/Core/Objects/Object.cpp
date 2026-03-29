#include "Object.h"

namespace Core {
	Object::Object() = default;
	Object::~Object() = default;

	void Object::SetName(const std::string& newName) {
		_name = newName;
	}
	std::string Object::GetName() {
		return _name;
	}

	bool Object::AddComponent(Component& component) {
		if (!component.CheckAddPossibility(*this)) {
			Logger::LogError("Component didn't attached: " + __LOGERROR__);
			return false;
		}

		// Check if component is already added
		for (auto* c : _components) {
			if (c == &component) {
				Logger::LogError("Component already attached: " + __LOGERROR__);
				return false;  // do not add again
			}
		}

		// Add component
		_components.push_back(&component);
		component._parentObject = this;
		component.OnParentObjectChanged(*this);
		Logger::LogInfo("Component attached successfully");
		return true;
	}

	bool Object::DetachComponent(Component& ref) {
		for (auto it = _components.begin(); it != _components.end(); ++it) {
			if (*it == &ref) {
				_components.erase(it);
				Logger::LogInfo("Component successfully detached");
				return true;
			}
		}

		Logger::LogInfo("Component didn't finded: " + __LOGERROR__);
		return false;
	}

	size_t Object::GetCountOfComponents() const {
		return Object::_components.size();
	}

	std::vector<Component*> Object::GetComponents() {
		return _components;
	}

	const Component& Object::GetComponentByIndex(size_t index) const {
		if (index >= _components.size())
		{
			Logger::LogCritical(
				"Component index out of range: " + __LOGERROR__
			);
		}

		return *_components[index];
	}
}