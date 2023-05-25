#include "Object.h"

#include "Modules/Geometry.h"
#include "Modules/Module.h"


#include "Vectors.h"

#include "World.h"

inline Vector3 Object::GetPosition() {
	return Position;
}
inline void Object::AddPosition(float X, float Y, float Z) {
	Object::Position.X += X;
	Object::Position.Y += Y;
	Object::Position.Z += Z;
}
inline void Object::AddPosition(Vector3 position) {
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
	Object::_transformMatrix.Rotation(Vector4(X, Y, Z, 1));

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
inline void Object::AddRotation(Vector3 rotation) {
	Object::_transformMatrix.Rotation(Vector4(rotation.X, rotation.Y, rotation.Z, 1));

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

	Object::_transformMatrix.Scale(Vector4(1 / delta.X, 1 / delta.Y, 1 / delta.Z, 1));

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
inline void Object::SetScale(Vector3 scale) {
	Vector3 delta = Object::Scale / scale;

	Object::_transformMatrix.Scale(Vector4(1 / delta.X, 1 / delta.Y, 1 / delta.Z, 1));

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


inline void Object::ApplyTransform() {
	Matrix4x4 buffer = Object::_transformMatrix.GetMatrix();

	for (size_t it = 0; it < Object::GetCountOfModules(); it++)
	{
		Geometry* geometry = dynamic_cast<Geometry*>(Object::GetModuleByIndex(it));

		if (geometry != nullptr && geometry->_isShifted == true) {
			geometry->ApplyTransformation();
		}
	}

	Object::_transformMatrix.Identity();
}

inline bool Object::AddModule(class Module* some_module) {
	Object::Modules.push_back(some_module);
	some_module->ParentObject = this;
	return true;
}
inline bool Object::AddModule(ModulesList moduleType) {
	switch (moduleType)
	{
	case ModuleType:
		return false;
		break;
	case CameraType:
		Object::AddModule(new Camera);
		break;
	case RigidBodyType:
		//Object::AddModule(new RigidBody);
		break;
	case GeometryType:
		Object::AddModule(new Geometry);
		break;
	case ColliderType:
		Object::AddModule(new Collider);
		break;
	case MeshType:
		Object::AddModule(new Mesh);
		break;
	default:
		return false;
		break;
	}

	return true;
}

inline int Object::GetCountOfModules() {
	return Object::Modules.size();
}


inline bool Object::DeleteModuleByType(ModulesList type) {
	for (size_t i = 0; i < Object::Modules.size(); i++) {
		if (type == Object::Modules[i]->GetType()) {
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

inline Module* Object::GetModuleByType(ModulesList type) {
	for (size_t i = 0; i < Object::Modules.size(); i++) {
		if (type == Object::Modules[i]->GetType()) {
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

inline unsigned long Object::GetGeometryHeaviness() {
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

inline Object::Object() {
	Object::_transformMatrix = Matrix4x4();

	World::ObjectsOnScene.push_back(this);
}

inline Object::~Object() {

}