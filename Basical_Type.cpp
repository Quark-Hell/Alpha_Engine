#include "Basical_Type.h"
#include <iostream>
#include <vector>

#pragma region Object Define

void Object::SetPosition (float X, float Y, float Z) {
	Object::Position.X = X;
	Object::Position.Y = Y;
	Object::Position.Z = Z;
}

Vector3 Object::GetPosition() {
	return Position;
}

bool Object::AddModule(class Module some_module) {
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

bool Object::DeleteModuleByType(class Module some_module) {
	try
	{
		std::string name = some_module.GetName();

		for (size_t i = 0; i < Object::Modules.size(); i++) {
			if (name == Object::Modules[i].GetName()) {
				Object::Modules.erase(Object::Modules.begin() + i - 1);
				return true;
			}
		}

		return false;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

bool Object::DeleteModuleByName(std::string name) {
	for (size_t i = 0; i < Object::Modules.size(); i++) {

	}
	return true;
}

#pragma endregion

#pragma region Module Define

bool Module::Rename(std::string name) {
	//TODO:
	Module::Name = name;
	return true;
}


std::string Module::GetName() {
	return Module::Name;
}

#pragma endregion

#pragma region Mesh Define
bool Mesh::CreateMesh(std::vector<Vector3> points, std::vector < Vector3> triangles) {
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

void Mesh::DeleteMesh() {
	Mesh::Points.clear();
	Mesh::Triangles.clear();
}

#pragma endregion


