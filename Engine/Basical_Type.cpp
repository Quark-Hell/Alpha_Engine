#include "Basical_Type.h"

#pragma region World Define

inline World::World() {

}

inline void World::CloseGame() {
	IsCloseGame = true;
}

inline bool World::GetStateOfGame() {
	return IsCloseGame;
}

#pragma endregion

#pragma region Object Define

inline Vector3 Object::GetPosition() {
	return Position;
}
inline void Object::SetPosition (float X, float Y, float Z) {
	Object::Position.X = X;
	Object::Position.Y = Y;
	Object::Position.Z = Z;
}
inline void Object::SetPosition(Vector3 Position) {
	Object::Position.X = Position.X;
	Object::Position.Y = Position.Y;
	Object::Position.Z = Position.Z;
}


inline Vector3 Object::GetRotation() {
	return Rotation;
}
inline void Object::SetRotation(float X, float Y, float Z) {
	Object::Rotation.X = X;
	Object::Rotation.Y = Y;
	Object::Rotation.Z = Z;
}
inline void Object::SetRotation(Vector3 Rotation) {
	Object::Rotation.X = Rotation.X;
	Object::Rotation.Y = Rotation.Y;
	Object::Rotation.Z = Rotation.Z;
}


inline Vector3 Object::GetScale() {
	return Scale;
}
inline void Object::SetScale(float X, float Y, float Z) {
	Object::Scale.X = X;
	Object::Scale.Y = Y;
	Object::Scale.Z = Z;
}
inline void Object::SetScale(Vector3 Scale) {
	Object::Scale.X = Scale.X;
	Object::Scale.Y = Scale.Y;
	Object::Scale.Z = Scale.Z;
}

inline bool Object::AddModule(class Module *some_module) {
	Object::Modules.push_back(some_module);
	some_module->ParentObject = this;
	return true;
}

inline int Object::GetCountOfModules() {
	return Object::Modules.size();
}

inline bool Object::DeleteModuleByName(std::string name) {
	for (size_t i = 0; i < Object::Modules.size(); i++) {
		if (name == Object::Modules[i]->GetName()) {
			Object::Modules.erase(Object::Modules.begin() + i);
			return true;
		}
	}

	return false;
}
inline bool Object::DeleteModuleByIndex(int index) {
	if (index >= 0 && index < Object::Modules.size()) {
		Object::Modules.erase(Object::Modules.begin() + index);
		return true;
	}

	return false;
}

inline Module* Object::GetModuleByName(std::string name) {
	for (size_t i = 0; i < Object::Modules.size(); i++) {
		if (name == Object::Modules[i]->GetName()) {
			return Object::Modules[i];
		}
	}

	return nullptr;
}
inline Module* Object::GetModuleByIndex(size_t index) {
	if (index >= 0 && index < Object::Modules.size()) {
		return Object::Modules[index];
	}

	return nullptr;
}

inline void Object::DeleteObject() {
	Object::~Object();
}

/*
inline void Object::DeleteObject() {
	for (size_t i = 0; i < World::ObjectsOnScene.size(); i++)
	{
		if (this == &World::ObjectsOnScene[i]) {
			World::ObjectsOnScene.erase(World::ObjectsOnScene.begin() + i);
			free(this);
		}
	}	
}
*/

inline Object::Object() {
	World::ObjectsOnScene.push_back(this);
}

inline Object::~Object() {

}

#pragma endregion

#pragma region Module Define

inline void Module::Rename(std::string name) {
	Module::_name = name;
}
inline std::string Module::GetName() {
	return Module::_name;
}

inline Object* Module::GetParentObject() {
	return ParentObject;
}

inline void Module::Test() {

}
#pragma endregion
