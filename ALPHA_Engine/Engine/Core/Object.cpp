#include "Object.h"

#include "BaseConfig.h"
#include "Factory.h"
#include "Components/Component.h"

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

bool Core::Object::AddComponent(Core::Component* component) {
	if (component == nullptr) {
		std::cout << "Component did not attached" << std::endl;
		return  false;
	}
	_components.push_back(component);
	component->ParentObject = this;
	std::cout << "Component attached successfully" << std::endl;

	return true;
}

size_t Core::Object::GetCountOfComponents() const {
	return Object::_components.size();
}

