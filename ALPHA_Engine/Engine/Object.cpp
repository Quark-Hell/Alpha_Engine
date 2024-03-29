#include "Object.h"

#include "Modules/Module.h"
#include "Modules/Camera.h"
#include "Modules/Geometry.h"
#include "Modules/Mesh.h"
#include "Modules/Physics.h"
#include "Modules/ColliderPresets.h"

#include "Modules/MeshCollider.h"
#include "Modules/BoxCollider.h"

#include "Collision.h"

#include "Vectors.h"
#include "World.h"

const BoxCollider& Object::GetInertiaCollider() {
	return Object::InertiaCollider;
}

Vector3 Object::GetPosition() {
	return Object::_position;
}

void Object::AddPosition(float X, float Y, float Z) {
	Object::_position.X += X;
	Object::_position.Y += Y;
	Object::_position.Z += Z;

	Object::_origin.X += X;
	Object::_origin.Y += Y;
	Object::_origin.Z += Z;

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		std::shared_ptr<Transform> transfrom = std::dynamic_pointer_cast<Transform>(Object::GetModuleByIndex(it));

		if (transfrom != nullptr) {
			transfrom->AddPosition(X, Y, Z);
		}
	}
}
void Object::AddPosition(Vector3 position) {
	Object::_position += position;
	Object::_origin += position;

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		std::shared_ptr<Transform> transfrom = std::dynamic_pointer_cast<Transform>(Object::GetModuleByIndex(it));

		if (transfrom != nullptr) {
			transfrom->AddPosition(position);
		}
	}
}
void Object::SetPosition(float X, float Y, float Z) {
	Vector3 direction = Vector3(X, Y, Z) - Object::_position;

	Object::AddPosition(direction);
}
void Object::SetPosition(Vector3 position) {
	Vector3 direction = position - Object::_position;

	Object::AddPosition(direction);
}

void Object::AddOriginPosition(float X, float Y, float Z) {
	Object::_origin.X += X;
	Object::_origin.Y += Y;
	Object::_origin.Z += Z;

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		std::shared_ptr<Transform> transfrom = std::dynamic_pointer_cast<Transform>(Object::GetModuleByIndex(it));

		if (transfrom != nullptr) {
			transfrom->AddOriginPosition(X, Y, Z);
		}
	}
}
void Object::AddOriginPosition(Vector3 position) {
	Object::_origin += position;

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		std::shared_ptr<Transform> transfrom = std::dynamic_pointer_cast<Transform>(Object::GetModuleByIndex(it));

		if (transfrom != nullptr) {
			transfrom->AddOriginPosition(position);
		}
	}
}

void Object::SetOriginPosition(float X, float Y, float Z) {
	Vector3 direction = Vector3(X, Y, Z) - Object::_origin;

	Object::AddOriginPosition(direction);
}
void Object::SetOriginPosition(Vector3 position) {
	Vector3 direction = position - Object::_origin;

	Object::AddOriginPosition(direction);
}


Vector3 Object::GetRotation() {
	return Object::_rotation;
}
void Object::AddRotation(float X, float Y, float Z) {
	const float radX = M_PI / 180 * X;
	const float radY = M_PI / 180 * Y;
	const float radZ = M_PI / 180 * Z;

	Object::_transformMatrix = glm::rotate(Object::_transformMatrix, radX, glm::vec3(1.0f, 0.0f, 0.0f));
	Object::_transformMatrix = glm::rotate(Object::_transformMatrix, radY, glm::vec3(0.0f, 1.0f, 0.0f));
	Object::_transformMatrix = glm::rotate(Object::_transformMatrix, radZ, glm::vec3(0.0f, 0.0f, 1.0f));

	Object::_rotation.X += X;
	Object::_rotation.Y += Y;
	Object::_rotation.Z += Z;

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		std::shared_ptr<Geometry> geometry = std::dynamic_pointer_cast<Geometry>(Object::GetModuleByIndex(it));

		if (geometry != nullptr) {
			geometry->_isShifted = true;
		}
	}
}
void Object::AddRotation(Vector3 rotation) {
	const float radX = M_PI / 180 * rotation.X;
	const float radY = M_PI / 180 * rotation.Y;
	const float radZ = M_PI / 180 * rotation.Z;

	Object::_transformMatrix = glm::rotate(Object::_transformMatrix, radX, glm::vec3(1.0f, 0.0f, 0.0f));
	Object::_transformMatrix = glm::rotate(Object::_transformMatrix, radY, glm::vec3(0.0f, 1.0f, 0.0f));
	Object::_transformMatrix = glm::rotate(Object::_transformMatrix, radZ, glm::vec3(0.0f, 0.0f, 1.0f));

	Object::_rotation.X += rotation.X;
	Object::_rotation.Y += rotation.Y;
	Object::_rotation.Z += rotation.Z;

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{	
		std::shared_ptr<Geometry> geometry = std::dynamic_pointer_cast<Geometry>(Object::GetModuleByIndex(it));

		if (geometry != nullptr) {
			geometry->_isShifted = true;
		}
	}
}
void Object::SetRotation(float X, float Y, float Z) {
	Vector3 direction = Vector3(X, Y, Z) - Object::_rotation;

	Object::AddRotation(direction);
}
void Object::SetRotation(Vector3 rotation) {
	Vector3 direction = rotation - Object::_rotation;

	Object::AddRotation(direction);
}


Vector3 Object::GetScale() {
	return Object::_scale;
}
void Object::SetScale(float X, float Y, float Z) {
	Vector3 delta = Object::_scale / Vector3(X, Y, Z);
	Object::_transformMatrix = glm::scale(Object::_transformMatrix, glm::vec3(1 / delta.X, 1 / delta.Y, 1 / delta.Z));

	Object::_scale.X = X;
	Object::_scale.Y = Y;
	Object::_scale.Z = Z;

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		std::shared_ptr<Geometry> geometry = std::dynamic_pointer_cast<Geometry>(Object::GetModuleByIndex(it));

		if (geometry != nullptr) {
			geometry->_isShifted = true;
		}
	}

	Object::ApplyTransformation();
}
void Object::SetScale(Vector3 scale) {
	Vector3 delta = Object::_scale / scale;
	Object::_transformMatrix = glm::scale(Object::_transformMatrix, glm::vec3(1 / delta.X, 1 / delta.Y, 1 / delta.Z));

	Object::_scale.X = scale.X;
	Object::_scale.Y = scale.Y;
	Object::_scale.Z = scale.Z;

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		std::shared_ptr<Geometry> geometry = std::dynamic_pointer_cast<Geometry>(Object::GetModuleByIndex(it));

		if (geometry != nullptr) {
			geometry->_isShifted = true;
		}
	}

	Object::ApplyTransformation();
}

void Object::ApplyTransformation() {
	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		std::shared_ptr<Geometry> geometry = std::dynamic_pointer_cast<Geometry>(Object::GetModuleByIndex(it));

		if (geometry != nullptr && geometry->_isShifted == true) {
			geometry->ApplyTransformation();
		}
	}

	Object::_transformMatrix = glm::mat4x4(1.0f);
}

bool Object::AddModule(std::shared_ptr<Module> someModule) {
	Object::Modules.push_back(someModule);
	someModule->SetParentObject(*this);
	return true;
}
bool Object::AddModule(ModulesList moduleType, Module& outputModule) {
	std::shared_ptr<Module> someModule;

	switch (moduleType)
	{
	case ModuleType:
		return false;
		break;
	case CameraType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<Camera>());
		break;
	case RigidBodyType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<RigidBody>());
		break;
	case GeometryType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<Geometry>());
		break;
	case MeshColliderType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<MeshCollider>());
		break;
	case BoxColliderType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<BoxCollider>());
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

std::shared_ptr<Module> Object::GetModuleByType(ModulesList type) {
	for (size_t i = 0; i < Object::Modules.size(); i++) {
		if (type == Object::Modules[i]->GetType()) {
			return Object::Modules[i];
		}
	}

	return nullptr;
}
std::vector<std::shared_ptr<Module>> Object::GetModuleByTypes(std::vector<ModulesList> typesArray) {
	std::vector<std::shared_ptr<Module>> buffer;

	for (size_t i = 0; i < Object::Modules.size(); i++) {
		for (size_t j = 0; j < typesArray.size(); j++) {
			if (typesArray[j] == Object::Modules[i]->GetType()) {
				buffer.push_back(Object::Modules[i]);
			}
		}
	}

	return buffer;
}

std::shared_ptr<Module> Object::GetModuleByIndex(size_t index) {
	if (index >= 0 && index < Object::Modules.size()) {
		return Object::Modules[index];
	}

	return nullptr;
}

glm::mat4x4& Object::GetTransformationMatrix() {
	return Object::_transformMatrix;
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
		std::shared_ptr<Geometry> geometry = std::dynamic_pointer_cast<Geometry>(Object::GetModuleByIndex(it));

		if (geometry != nullptr && geometry->_isShifted == true) {
			heaviness += geometry->_vertexCount;
			heaviness += geometry->_normalsCount;
		}
	}

	return heaviness;
}

Object::Object() {
	bool isHave = false;
	for (size_t i = 0; i < World::ObjectsOnScene.size(); i++) {
		if (this == World::ObjectsOnScene[i]) {
			isHave = true;
		}
	}

	if (isHave == true)
		return;

	World::ObjectsOnScene.push_back(this);
}

Object::~Object() {
	for (size_t i = 0; i < World::ObjectsOnScene.size(); i++) {
		if (this == World::ObjectsOnScene[i]) {
			World::ObjectsOnScene.erase(World::ObjectsOnScene.begin() + i);
		}
	}
}