#include "Object.h"

#include "BaseConfig.h"

#include "Core/Modules/Transform.h"
#include "Core/Modules/Module.h"
#include "Core/Tag.h"

#include "ModuleList.h"

Core::Object::Object() {
	//World::ObjectsOnScene.push_back(this);
}

Core::Object::~Object() {
	//for (size_t i = 0; i < World::ObjectsOnScene.size(); i++) {
	//	if (this == World::ObjectsOnScene[i]) {
	//		World::ObjectsOnScene.erase(World::ObjectsOnScene.begin() + i);
	//		return;
	//	}
	//}
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

bool Core::Object::AddModule(std::shared_ptr<Core::Module> someModule) {
	Object::_modules.push_back(someModule);
	someModule->SetParentObject(*this);
	return true;
}
bool Core::Object::AddModule(ModulesList moduleType, Core::Module** outputModule) {
	std::shared_ptr<Core::Module> someModule;

	switch (moduleType)
	{
	case ModuleType:
		return false;
		break;
#if __has_include("Camera.h")
	case CameraType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<Camera>());
		break;
#endif
#if __has_include("Rigidbody.h")
	case RigidBodyType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<RigidBody>());
		break;
#endif
#if __has_include("Geometry.h")
	case GeometryType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<Geometry>());
		break;
#endif
#if __has_include("MeshCollider.h")
	case MeshColliderType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<MeshCollider>());
		break;
#endif
#if __has_include("Mesh.h")
	case MeshType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<Mesh>());
		break;
#endif
#if __has_include("BoxCollider.h")
	case BoxColliderType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<BoxCollider>());
		break;
#endif
	default:
		return false;
		break;
	}


	Object::AddModule(someModule);
	*outputModule = someModule.get();

	return true;
}
bool Core::Object::AddModule(ModulesList moduleType) {
	std::shared_ptr<Core::Module> someModule;

	switch (moduleType)
	{
	case ModuleType:
		return false;
		break;
#if __has_include("Camera.h")
	case CameraType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<Camera>());
		break;
#endif
#if __has_include("Rigidbody.h")
	case RigidBodyType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<RigidBody>());
		break;
#endif
#if __has_include("Geometry.h")
	case GeometryType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<Geometry>());
		break;
#endif
#if __has_include("MeshCollider.h")
	case MeshColliderType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<MeshCollider>());
		break;
#endif
#if __has_include("Mesh.h")
	case MeshType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<Mesh>());
		break;
#endif
#if __has_include("BoxCollider.h")
	case BoxColliderType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<BoxCollider>());
		break;
#endif
	default:
		return false;
		break;
	}

	//Object::AddModule(someModule);
	return true;
}

int Core::Object::GetCountOfModules() {
	return Object::_modules.size();
}


bool Core::Object::DeleteModuleByType(ModulesList type) {
	for (size_t i = 0; i < Object::_modules.size(); i++) {
		if (type == Object::_modules[i]->GetType()) {
			Object::_modules.erase(Object::_modules.begin() + i);
			return true;
		}
	}

	return false;
}
bool Core::Object::DeleteModuleByIndex(int index) {
	if (index >= 0 && index < Object::_modules.size()) {
		Object::_modules.erase(Object::_modules.begin() + index);
		return true;
	}

	return false;
}

std::shared_ptr<Core::Module> Core::Object::GetModuleByType(ModulesList type) {
	for (size_t i = 0; i < Object::_modules.size(); i++) {
		if (type == Object::_modules[i]->GetType()) {
			return Object::_modules[i];
		}
	}

	return nullptr;
}
std::vector<std::shared_ptr<Core::Module>> Core::Object::GetModuleByTypes(std::vector<ModulesList> typesArray) {
	std::vector<std::shared_ptr<Core::Module>> buffer;

	for (size_t i = 0; i < Core::Object::_modules.size(); i++) {
		for (size_t j = 0; j < typesArray.size(); j++) {
			if (typesArray[j] == Object::_modules[i]->GetType()) {
				buffer.push_back(Object::_modules[i]);
			}
		}
	}

	return buffer;
}

std::shared_ptr<Core::Module> Core::Object::GetModuleByIndex(size_t index) {
	if (index >= 0 && index < Object::_modules.size()) {
		return Object::_modules[index];
	}

	return nullptr;
}
