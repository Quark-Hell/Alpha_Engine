#include "Component.h"
#include "Core/Objects/Object.h"

namespace Core {
	Component::~Component() = default;

	void Component::UpdateParentObject() {

	}

	Core::Object* Component::GetParentObject() {
		return ParentObject;
	}
}

