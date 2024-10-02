#include "Object.h"

#include "BaseConfig.h"

#include "Components/Transform.h"
#include "Components/Component.h"
#include "Tag.h"
#include "Core/World.h"

Core::Object::Object() {

}

std::shared_ptr<Core::Object> Core::Object::CreateObject() {
	Core::Object* obj = new Core::Object();
	World::GetObjects().push_back(std::shared_ptr<Core::Object>(obj));
	return World::GetObjects().back();
}

Core::Object::~Object() {
	std::list<std::shared_ptr<Core::Object>> list = Core::World::GetObjects();
	size_t t = 0;

	for (auto i : list) {
		if (i.get() == this) {
			auto it = list.begin();
			std::advance(it, t);

			list.erase(it);
			return;
		}
		t++;
	}
}

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

