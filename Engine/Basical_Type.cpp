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
inline Module* Object::GetModuleByIndex(int index) {
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

inline void Module::Test() {

}
#pragma endregion


#pragma region Mesh Define
inline Mesh::Mesh() {
	Mesh::Rename("Mesh");
}

inline Mesh::~Mesh() {

}

inline bool Mesh::CreateMesh(std::string linkToFBX) {
	Assimp::Importer importer;
	std::string path = std::filesystem::current_path().string() + linkToFBX.c_str();

	//TODO: Check if fbx
	const aiScene* s = importer.ReadFile(path, aiProcess_Triangulate);
	aiMesh* mesh = s->mMeshes[0];

	Mesh::Points.clear();
	Mesh::Normals.clear();

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

