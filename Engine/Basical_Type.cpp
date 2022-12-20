#include "Basical_Type.h"
#include <iostream>
#include <vector>
#include <typeinfo>
#include <type_traits>

#pragma region Object Define

inline void Object::SetPosition (float X, float Y, float Z) {
	Object::Position.X = X;
	Object::Position.Y = Y;
	Object::Position.Z = Z;
}

inline Vector3 Object::GetPosition() {
	return Position;
}

inline bool Object::AddModule(class Module some_module) {
	try
	{
		Object::Modules.push_back(some_module);
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

inline bool Object::DeleteModuleByName(std::string name) {
	for (size_t i = 0; i < Object::Modules.size(); i++) {
		if (name == Object::Modules[i].GetName()) {
			Object::Modules.erase(Object::Modules.begin() + i);
			return true;
		}
	}

	return true;
}

inline bool Object::DeleteModuleByIndex(int index) {
	if (index >= 0 && index < Object::Modules.size()) {
		Object::Modules.erase(Object::Modules.begin() + index);
		return true;
	}
	else
	{
		return false;
	}
}

inline Module* Object::GetModuleByName(std::string name) {
	for (size_t i = 0; i < Object::Modules.size(); i++) {
		if (name == Object::Modules[i].GetName()) {
			return &Object::Modules[i];
		}
	}

	return nullptr;
}

inline Module* Object::GetModuleByIndex(int index) {
	if (index >= 0 && index < Object::Modules.size()) {
		return &Object::Modules[index];
	}
	else
	{
		return nullptr;
	}
}

#pragma endregion

#pragma region Module Define

inline bool Module::Rename(std::string name) {
	//TODO:
	Module::Name = name;
	return true;
}

inline std::string Module::GetName() {
	return Module::Name;
}

inline int Object::GetCountOfModules() {
	return Object::Modules.size();
}

#pragma endregion

#pragma region Mesh Define
inline bool Mesh::CreateMesh(std::vector<Vector3> points, std::vector < Vector3> triangles) {
	try
	{
		for (size_t i = 0; i < points.size(); i++) {
			Mesh::Points[i] = points[i];
		}
		for (size_t i = 0; i < triangles.size(); i++) {
			Mesh::Triangles[i] = triangles[i];
		}
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

inline void Mesh::DeleteMesh() {
	Mesh::Points.clear();
	Mesh::Triangles.clear();
}

#pragma endregion


