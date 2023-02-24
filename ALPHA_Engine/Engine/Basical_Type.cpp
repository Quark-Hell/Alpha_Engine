#include "Basical_Type.h"
#include "Mesh.cpp"

#pragma region World Define

inline World::World() {

}

inline void World::CloseGame() {
	IsCloseGame = true;
}

inline bool World::GetStateOfGame() {
	return IsCloseGame;
}

inline double World::GetTimeLong() {
	return World::_timeLong;
}
inline float World::GetDeltaTime() {
	return World::_deltaTime;
}

inline void World::StartFrame() {
	// Get starting timepoint
	World::_startTime = std::chrono::high_resolution_clock::now();
}
inline void World::EndFrame() {
	World::_endTime = std::chrono::high_resolution_clock::now();
	World::_deltaTime = std::chrono::duration_cast	<std::chrono::milliseconds>(World::_endTime - World::_startTime).count();
	World::_timeLong += std::chrono::duration_cast	<std::chrono::milliseconds>(World::_endTime - World::_startTime).count();
}

#pragma endregion

#pragma region Object Define

inline Vector3 Object::GetPosition() {
	return Position;
}
inline void Object::AddPosition (float X, float Y, float Z) {
	Matrix4x4 matrix = Matrix4x4();
	matrix.Translation(Vector4(X, Y, Z, 1));

	MatrixMath::MultiplyMatrix(Object::_transformMatrix, Object::_transformMatrix.GetMatrix(), matrix);

	Object::Position.X += X;
	Object::Position.Y += Y;
	Object::Position.Z += Z;
}
inline void Object::AddPosition(Vector3 position) {
	Matrix4x4 matrix = Matrix4x4();
	matrix.Translation(Vector4(position.X, position.Y, position.Z, 1));

	MatrixMath::MultiplyMatrix(Object::_transformMatrix, Object::_transformMatrix.GetMatrix(), matrix);

	Object::Position.X += position.X;
	Object::Position.Y += position.Y;
	Object::Position.Z += position.Z;

}
inline void Object::SetPosition(float X, float Y, float Z) {
	Vector3 direction = Vector3(X, Y, Z) - Object::Position;

	Object::AddPosition(direction);
}
inline void Object::SetPosition(Vector3 position) {
	Vector3 direction = position - Object::Position;

	Object::AddPosition(direction);
}


inline Vector3 Object::GetRotation() {
	return Rotation;
}
inline void Object::AddRotation(float X, float Y, float Z) {
	Matrix4x4 matrix = Matrix4x4();
	matrix.Rotation(Vector4(X, Y, Z, 1));

	MatrixMath::MultiplyMatrix(Object::_transformMatrix, Object::_transformMatrix.GetMatrix(), matrix);

	Object::Rotation.X += X;
	Object::Rotation.Y += Y;
	Object::Rotation.Z += Z;

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		Mesh* mesh = dynamic_cast<Mesh*>(Object::GetModuleByIndex(it));

		if (mesh != nullptr && mesh->GetName() == "Mesh") {
			mesh->_isShifted = true;
		}
	}
}
inline void Object::AddRotation(Vector3 rotation) {
	Matrix4x4 matrix = Matrix4x4();
	matrix.Rotation(Vector4(rotation.X, rotation.Y, rotation.Z, 1));

	MatrixMath::MultiplyMatrix(Object::_transformMatrix, Object::_transformMatrix.GetMatrix(), matrix);

	Object::Rotation.X += rotation.X;
	Object::Rotation.Y += rotation.Y;
	Object::Rotation.Z += rotation.Z;

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		Mesh* mesh = dynamic_cast<Mesh*>(Object::GetModuleByIndex(it));

		if (mesh != nullptr && mesh->GetName() == "Mesh") {
			mesh->_isShifted = true;
		}
	}
}
inline void Object::SetRotation(float X, float Y, float Z) {
	Vector3 direction = Vector3(X, Y, Z) - Object::Rotation;

	Object::AddRotation(direction);
}
inline void Object::SetRotation(Vector3 rotation) {
	Vector3 direction = rotation - Object::Rotation;

	Object::AddRotation(direction);
}


inline Vector3 Object::GetScale() {
	return Scale;
}
inline void Object::SetScale(float X, float Y, float Z) {
	Vector3 delta = Object::Scale / Vector3(X, Y, Z);

	Matrix4x4 matrix = Matrix4x4();

	matrix.Scale(Vector4(1 / delta.X, 1 / delta.Y, 1 / delta.Z, 1));

	MatrixMath::MultiplyMatrix(Object::_transformMatrix, Object::_transformMatrix.GetMatrix(), matrix);

	Object::Scale.X = X;
	Object::Scale.Y = Y;
	Object::Scale.Z = Z;

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		Mesh* mesh = dynamic_cast<Mesh*>(Object::GetModuleByIndex(it));

		if (mesh != nullptr && mesh->GetName() == "Mesh") {
			mesh->_isShifted = true;
		}
	}
}
inline void Object::SetScale(Vector3 scale) {
	Vector3 delta = Object::Scale / scale;
	Matrix4x4 matrix = Matrix4x4();

	matrix.Scale(Vector4(1 / delta.X, 1 / delta.Y, 1 / delta.Z, 1));

	MatrixMath::MultiplyMatrix(Object::_transformMatrix, Object::_transformMatrix.GetMatrix(), matrix);

	Object::Scale.X = scale.X;
	Object::Scale.Y = scale.Y;
	Object::Scale.Z = scale.Z;

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		Mesh* mesh = dynamic_cast<Mesh*>(Object::GetModuleByIndex(it));

		if (mesh != nullptr && mesh->GetName() == "Mesh") {
			mesh->_isShifted = true;
		}
	}
}


inline void Object::ApplyTransform() {
	Matrix4x4 buffer = Object::_transformMatrix.GetMatrix();

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		Mesh* mesh = dynamic_cast<Mesh*>(Object::GetModuleByIndex(it));

		if (mesh != nullptr && mesh->GetName() == "Mesh" && mesh->_isShifted == true) {
			for (size_t jt = 0; jt < mesh->_vertexCount * 3; jt+=3)
			{
				std::array<float, 4> buffer;
				buffer[0] = mesh->_vertex[jt];
				buffer[1] = mesh->_vertex[jt + 1];
				buffer[2] = mesh->_vertex[jt + 2];
				buffer[3] = 1;

				float w = 1;

				//MatrixMath::MultiplyMatrix(mesh->_vertex[jt], Object::_transformMatrix , buffer);

				MatrixMath::MultiplyMatrix(
					mesh->_vertex[jt], 
					mesh->_vertex[jt+1], 
					mesh->_vertex[jt+2],
					w, 
					Object::_transformMatrix, buffer);
			}
			mesh->_isShifted = false;
		}
	}

	Object::_transformMatrix.Identity();
	//Vector4 posMatrix = Position;
	//Vector4 rotMatrix = Rotation;
	//Vector4 scaleMatrix = Scale;

	//MatrixMath::MultiplyMatrix(Position, buffer, posMatrix);
	//MatrixMath::MultiplyMatrix(Rotation, buffer, rotMatrix);
	//MatrixMath::MultiplyMatrix(Scale,	 buffer, scaleMatrix);
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
	_name = name;
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
