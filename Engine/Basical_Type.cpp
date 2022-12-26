#include "Basical_Type.h"
#include <iostream>
#include <vector>

//Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma region World Define

//std::vector<Object> World::ObjectsOnScene;
//World::_Static World::global{};

inline::World::World() {

}

#pragma endregion


#pragma region Object Define

inline void Object::SetPosition (float X, float Y, float Z) {
	Object::Position.X = X;
	Object::Position.Y = Y;
	Object::Position.Z = Z;
}

inline Vector3 Object::GetPosition() {
	return Position;
}

inline void Object::SetRotation(float X, float Y, float Z) {
	Object::Rotation.X = X;
	Object::Rotation.Y = Y;
	Object::Rotation.Z = Z;
}

inline Vector3 Object::GetRotation() {
	return Rotation;
}

inline void Object::SetScale(float X, float Y, float Z) {
	Object::Scale.X = X;
	Object::Scale.Y = Y;
	Object::Scale.Z = Z;
}

inline Vector3 Object::GetScale() {
	return Scale;
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

inline int Object::GetCountOfModules() {
	return Object::Modules.size();
}

inline bool Object::DeleteModuleByName(std::string name) {
	for (size_t i = 0; i < Object::Modules.size(); i++) {
		if (name == Object::Modules[i].GetName()) {
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

	return nullptr;
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
	//World::global.ObjectsOnScene.push_back(*this);
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

#pragma endregion


#pragma region Mesh Define
/*
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
*/

inline bool Mesh::CreateMesh(std::string linkToFBX) {
	Assimp::Importer importer;
	//TODO: Check if fbx
	const aiScene* s = importer.ReadFile(linkToFBX, aiProcess_Triangulate);
	aiMesh* mesh = s->mMeshes[0];

	for (std::uint32_t it = 0; it < mesh->mNumVertices; it++) {
		Vector3 point;
		Vector3 normal;

		if (mesh->HasPositions()) {
			point.X = mesh->mVertices[it].x;
			point.Y = mesh->mVertices[it].y;
			point.Z = mesh->mVertices[it].z;
		}

		if (mesh->HasNormals()) {
			normal.X = mesh->mNormals[it].x;
			normal.Y = mesh->mNormals[it].y;
			normal.Z = mesh->mNormals[it].z;
		}

		//if (mesh->HasVertexColors(0))v.color = vec4(mesh->mColors[0][it]);
		//if (mesh->HasTextureCoords(0))v.uv = vec2(mesh->mTextureCoords[0][it]);

		Mesh::Points.push_back(point);
		Mesh::Normals.push_back(normal);
	}

	return true;
}

inline void Mesh::DeleteMesh() {
	Mesh::Points.clear();
	Mesh::Normals.clear();
}

#pragma endregion


