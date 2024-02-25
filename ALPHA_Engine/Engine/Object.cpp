#include "Object.h"

#include "Modules/Module.h"
#include "Modules/Camera.h"
#include "Modules/Geometry.h"
#include "Modules/Mesh.h"
#include "Modules/Physics.h"
#include "Modules/Collider.h"

#include "Modules/MeshCollider.h"
#include "Modules/BoxCollider.h"

#include "Collision.h"

#include "Vectors.h"
#include "World.h"

Vector3 Object::GetPosition() {
	return Object::_position;
}

void Object::AddPosition(float X, float Y, float Z) {
	Object::_position.X += X;
	Object::_position.Y += Y;
	Object::_position.Z += Z;

	//Object::_transformMatrix = glm::translate(Object::_transformMatrix, glm::vec3(_position.X, _position.Y, _position.Z));

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		std::shared_ptr<Geometry> geometry = std::dynamic_pointer_cast<Geometry>(Object::GetModuleByIndex(it));

		if (geometry != nullptr) {
			geometry->_isShifted = true;
		}
	}

	//Object::ApplyTransformation();
}
void Object::AddPosition(Vector3 position) {
	Object::_position += position;

	//Object::_transformMatrix = glm::translate(Object::_transformMatrix, glm::vec3(_position.X, _position.Y, _position.Z));

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		std::shared_ptr<Geometry> geometry = std::dynamic_pointer_cast<Geometry>(Object::GetModuleByIndex(it));

		if (geometry != nullptr) {
			geometry->_isShifted = true;
		}
	}

	//Object::ApplyTransformation();
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
		std::shared_ptr<Geometry> geometry = std::dynamic_pointer_cast<Geometry>(Object::GetModuleByIndex(it));

		if (geometry != nullptr) {
			geometry->_isShifted = true;
		}
	}
}
void Object::AddOriginPosition(Vector3 position) {
	Object::_origin += position;

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		std::shared_ptr<Geometry> geometry = std::dynamic_pointer_cast<Geometry>(Object::GetModuleByIndex(it));

		if (geometry != nullptr) {
			geometry->_isShifted = true;
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


Vector4 Object::GetRotation() {
	return Object::_rotation;
}
void Object::AddRotation(float X, float Y, float Z) {
	const float radX = M_PI / 180.0f * X;
	const float radY = M_PI / 180.0f * Y;
	const float radZ = M_PI / 180.0f * Z;

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

	//Object::ApplyTransformation();
}
void Object::AddRotation(Vector3 rotation) {
	const float radX = M_PI / 180.0f * rotation.X;
	const float radY = M_PI / 180.0f * rotation.Y;
	const float radZ = M_PI / 180.0f * rotation.Z;

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

		std::shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera>(Object::GetModuleByIndex(it));
	}

	//Object::ApplyTransformation();
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

	Object::ApplyTransformation();
}
void Object::SetScale(Vector3 scale) {
	Vector3 delta = Object::_scale / scale;
	Object::_transformMatrix = glm::scale(Object::_transformMatrix, glm::vec3(1 / delta.X, 1 / delta.Y, 1 / delta.Z));

	Object::_scale.X = scale.X;
	Object::_scale.Y = scale.Y;
	Object::_scale.Z = scale.Z;

	Object::ApplyTransformation();
}

Vector3 Object::GetOriginPosition()
{
	return Object::_origin;
}

void Object::ApplyTransformation() {
	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		std::shared_ptr<MeshCollider> geometry = std::dynamic_pointer_cast<MeshCollider>(Object::GetModuleByIndex(it));

		if (geometry != nullptr && geometry->_isShifted == true) {
			geometry->ApplyTransformation();
			continue;
		}

		std::shared_ptr<Mesh> mesh = std::dynamic_pointer_cast<Mesh>(Object::GetModuleByIndex(it));

		if (mesh != nullptr) {
			mesh->ApplyTransformation();
			continue;
		}
	}

	Object::_transformMatrix = glm::mat4x4(1.0f);
}

bool Object::AddModule(std::shared_ptr<Module> someModule) {
	Object::Modules.push_back(someModule);
	someModule->SetParentObject(*this);
	return true;
}
bool Object::AddModule(ModulesList moduleType, Module** outputModule) {
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
	case MeshType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<Mesh>());
		break;
	case BoxColliderType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<BoxCollider>());
		break;
	default:
		return false;
		break;
	}


	Object::AddModule(someModule);
	*outputModule = someModule.get();

	return true;
}
bool Object::AddModule(ModulesList moduleType) {
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
	case MeshType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<Mesh>());
		break;
	case BoxColliderType:
		someModule = std::dynamic_pointer_cast<Module>(std::make_shared<BoxCollider>());

		break;
	default:
		return false;
		break;
	}

	Object::AddModule(someModule);
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
			heaviness += geometry->_vertex->size() / 3;
			heaviness += geometry->_normals->size() / 3;
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
			return;
		}
	}
}



Tag::Tag() {
	if (Tag::_availableTags.size() != 0) {
		Tag::_tag = Tag::_availableTags.begin()->first;
		return;
	}


	unsigned int count = 0;
	Tag::_availableTags.emplace(std::make_pair("Object", count++));
	Tag::_availableTags.emplace(std::make_pair("Player", count++));
	Tag::_availableTags.emplace(std::make_pair("SkyBox", count++));
}


bool Tag::SetTag(std::string tag)
{
	for (const auto& el : _availableTags) {
		if (el.first == tag) {
			Tag::_tag = tag;
			return true;
		}
	}
	return false;
}

bool Tag::SetTag(unsigned int tagIndex)
{
	if (tagIndex > Tag::_availableTags.size())
		return false;

	auto el = Tag::_availableTags.begin();
	std::advance(el, tagIndex);
	
	Tag::_tag = el->first;
	return true;
}

std::string Tag::GetTag()
{
	return Tag::_tag;
}

std::vector<std::string> Tag::GetAvailablesTag()
{
	std::vector<std::string> tags;
	tags.reserve(Tag::_availableTags.size());
	for (const auto& el : _availableTags) {
		tags.push_back(el.first);
	}

	return tags;
}
