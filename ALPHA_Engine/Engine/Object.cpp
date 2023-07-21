#include "Object.h"

#include "Modules/Module.h"
#include "Modules/Geometry.h"
#include "Modules/BoxCollider.h"

#include "Vectors.h"

#include "World.h"

Vector3 Object::GetPosition() {
	return Position;
}
void Object::AddPosition(float X, float Y, float Z) {
	Object::Position.X += X;
	Object::Position.Y += Y;
	Object::Position.Z += Z;
}
void Object::AddPosition(Vector3 position) {
	Object::Position.X += position.X;
	Object::Position.Y += position.Y;
	Object::Position.Z += position.Z;
}
void Object::SetPosition(float X, float Y, float Z) {
	Vector3 direction = Vector3(X, Y, Z) - Object::Position;

	Object::AddPosition(direction);
}
void Object::SetPosition(Vector3 position) {
	Vector3 direction = position - Object::Position;

	Object::AddPosition(direction);
}


Vector3 Object::GetRotation() {
	return Rotation;
}
void Object::AddRotation(float X, float Y, float Z) {
	const float radX = M_PI / 180 * X;
	const float radY = M_PI / 180 * Y;
	const float radZ = M_PI / 180 * Z;

	Object::_transformMatrix = glm::rotate(Object::_transformMatrix, radX, glm::vec3(1.0f, 0.0f, 0.0f));
	Object::_transformMatrix = glm::rotate(Object::_transformMatrix, radY, glm::vec3(0.0f, 1.0f, 0.0f));
	Object::_transformMatrix = glm::rotate(Object::_transformMatrix, radZ, glm::vec3(0.0f, 0.0f, 1.0f));
	
	//Object::_transformMatrix.Rotation(Vector4(X, Y, Z, 1));

	Object::Rotation.X += X;
	Object::Rotation.Y += Y;
	Object::Rotation.Z += Z;

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		Geometry* geometry = dynamic_cast<Geometry*>(Object::GetModuleByIndex(it));

		if (geometry != nullptr) {
			geometry->_isShifted = true;
		}
	}
}
void Object::AddRotation(Vector3 rotation) {
	//Object::_transformMatrix.Rotation(Vector4(rotation.X, rotation.Y, rotation.Z, 1));
	const float radX = M_PI / 180 * rotation.X;
	const float radY = M_PI / 180 * rotation.Y;
	const float radZ = M_PI / 180 * rotation.Z;

	Object::_transformMatrix = glm::rotate(Object::_transformMatrix, radX, glm::vec3(1.0f, 0.0f, 0.0f));
	Object::_transformMatrix = glm::rotate(Object::_transformMatrix, radY, glm::vec3(0.0f, 1.0f, 0.0f));
	Object::_transformMatrix = glm::rotate(Object::_transformMatrix, radZ, glm::vec3(0.0f, 0.0f, 1.0f));

	Object::Rotation.X += rotation.X;
	Object::Rotation.Y += rotation.Y;
	Object::Rotation.Z += rotation.Z;

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		Geometry* geometry = dynamic_cast<Geometry*>(Object::GetModuleByIndex(it));

		if (geometry != nullptr) {
			geometry->_isShifted = true;
		}
	}
}
void Object::SetRotation(float X, float Y, float Z) {
	Vector3 direction = Vector3(X, Y, Z) - Object::Rotation;

	Object::AddRotation(direction);
}
void Object::SetRotation(Vector3 rotation) {
	Vector3 direction = rotation - Object::Rotation;

	Object::AddRotation(direction);
}


Vector3 Object::GetScale() {
	return Scale;
}
void Object::SetScale(float X, float Y, float Z) {
	Vector3 delta = Object::Scale / Vector3(X, Y, Z);
	Object::_transformMatrix = glm::scale(Object::_transformMatrix, glm::vec3(1 / delta.X, 1/ delta.Y, 1 / delta.Z));

	Object::Scale.X = X;
	Object::Scale.Y = Y;
	Object::Scale.Z = Z;

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		Geometry* geometry = dynamic_cast<Geometry*>(Object::GetModuleByIndex(it));

		if (geometry != nullptr) {
			geometry->_isShifted = true;
		}
	}

	Object::ApplyTransform();
}
void Object::SetScale(Vector3 scale) {
	Vector3 delta = Object::Scale / scale;
	Object::_transformMatrix = glm::scale(Object::_transformMatrix, glm::vec3(1 / delta.X, 1 / delta.Y, 1 / delta.Z));

	Object::Scale.X = scale.X;
	Object::Scale.Y = scale.Y;
	Object::Scale.Z = scale.Z;

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		Geometry* geometry = dynamic_cast<Geometry*>(Object::GetModuleByIndex(it));

		if (geometry != nullptr) {
			geometry->_isShifted = true;
		}
	}

	Object::ApplyTransform();
}


void Object::ApplyTransform() {
	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		Geometry* geometry = dynamic_cast<Geometry*>(Object::GetModuleByIndex(it));

		if (geometry != nullptr && geometry->_isShifted == true) {
			geometry->ApplyTransformation();
		}
	}

	Object::_transformMatrix = glm::mat4x4(1.0f);
}

bool Object::AddModule(class Module* someModule) {
	Object::Modules.push_back(someModule);
	someModule->SetParentObject(*this);
	return true;
}
bool Object::AddModule(ModulesList moduleType, Module& outputModule) {
	Module *someModule;

	switch (moduleType)
	{
	case ModuleType:
		return false;
		break;
	case CameraType:
		someModule = new ModulesList::Camera;
		break;
	case RigidBodyType:
		someModule = new ModulesList::RigidBody;
		break;
	case GeometryType:
		someModule = new Geometry;
		break;
	case MeshColliderType:
		someModule = new ModulesList::MeshCollider;
		break;
	case BoxColliderType:
		someModule = new BoxCollider;
		break;
	default:
		return false;
		break;
	}

	Object::AddModule(someModule);
	someModule->SetParentObject(*this);
	return true;
}

int Object::GetCountOfModules() {
	return Object::Modules.size();
}


bool Object::DeleteModuleByType(ModulesList type) {
	for (size_t i = 0; i < Object::Modules.size(); i++) {
		if (type == Object::Modules[i]->GetType()) {
			Object::Modules.erase(Object::Modules.begin() + i);
			return true;
		}
	}

	return false;
}
bool Object::DeleteModuleByIndex(int index) {
	if (index >= 0 && index < Object::Modules.size()) {
		Object::Modules.erase(Object::Modules.begin() + index);
		return true;
	}

	return false;
}

Module* Object::GetModuleByType(ModulesList type) {
	for (size_t i = 0; i < Object::Modules.size(); i++) {
		if (type == Object::Modules[i]->GetType()) {
			return Object::Modules[i];
		}
	}

	return nullptr;
}
Module* Object::GetModuleByIndex(size_t index) {
	if (index >= 0 && index < Object::Modules.size()) {
		return Object::Modules[index];
	}

	return nullptr;
}

void Object::DeleteObject() {
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

unsigned long Object::GetGeometryHeaviness() {
	unsigned long heaviness = 0;

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		Object* obj = this;
		Geometry* geometry = dynamic_cast<Geometry*>(Object::GetModuleByIndex(it));

		if (geometry != nullptr && geometry->_isShifted == true) {
			heaviness += geometry->_vertexCount;
			heaviness += geometry->_normalsCount;
		}
	}

	return heaviness;
}

Object::Object() {
	Object::_transformMatrix = glm::mat4x4(1.0f);

	World::ObjectsOnScene.push_back(this);
}

Object::~Object() {

}