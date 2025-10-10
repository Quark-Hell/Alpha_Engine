#include "Component.h"
#include "Core/Objects/Object.h"

namespace Core {
	void Component::UpdateParentObject(Core::Object& newParent) {

	}

	bool Component::CheckAddPossibility(Core::Object& newParent) {
		return true;
	}

	Core::Object* Component::GetParentObject() {
		return ParentObject;
	}
}

