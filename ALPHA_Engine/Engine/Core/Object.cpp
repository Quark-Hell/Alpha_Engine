#include "Object.h"

#include "BaseConfig.h"
#include "Factory.h"

Core::Object::Object() = default;
Core::Object::~Object() = default;

Core::Object& Core::Object::CreateObject(const std::string& name) {
	auto obj = Core::Factory::CreateObject();
	obj._name = name;
	std::cout << "Name of object: " << obj._name << std::endl;
	return Core::Factory::CreateObject();
}

void Core::Object::Delete() {
	Object::~Object();
}

void Core::Object::SetName(const std::string &newName) {
	_name = newName;
}
std::string Core::Object::GetName() {
	return _name;
}

size_t Core::Object::GetCountOfComponents() const {
	return Object::_components.size();
}

