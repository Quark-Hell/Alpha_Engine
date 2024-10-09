#include "Object.h"

#include "BaseConfig.h"

#include "Components/Transform.h"
#include "Components/Component.h"
#include "Tag.h"
#include "Core/World.h"

Core::Object::Object() {

}

std::shared_ptr<Core::Object> Core::Object::CreateObject(const std::string& name) {
	World::GetObjects().push_back(std::shared_ptr<Core::Object>(new Core::Object()));
	World::GetObjects().back()->_name = name;
	std::cout << "Name of object: " << World::GetObjects().back()->_name << std::endl;
	return World::GetObjects().back();
}

Core::Object::~Object() = default;

void Core::Object::Delete() {
	Object::~Object();
}

void Core::Object::SetName(std::string newName) {
	_name = newName;
}
std::string Core::Object::GetName() {
	return _name;
}

int Core::Object::GetCountOfModules() {
	return Object::_modules.size();
}

