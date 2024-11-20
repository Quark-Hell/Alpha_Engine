#include "Component.h"
#include "Core/Object.h"

Core::Component::~Component() = default;

Core::Object* Core::Component::GetParentObject() {
	return ParentObject;
}