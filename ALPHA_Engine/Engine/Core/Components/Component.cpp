#include "Component.h"
#include "Core/Object.h"

Core::Component::Component() = default;
Core::Component::~Component() = default;

Core::Object& Core::Component::GetParentObject() {
	return *ParentObject;
}
void Core::Component::SetParentObject(const Core::Object& parent) {
	ParentObject = const_cast<Object*>(&parent);
}