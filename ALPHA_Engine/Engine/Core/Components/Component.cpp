#include "Component.h"
#include "Core/Objects/Object.h"

namespace Core {
	void Component::UpdateParentObject(Core::Object& newParent) {

	}

	bool Component::CheckAddPossibility(Core::Object& newParent) {
		return true;
	}

	Core::Object* Component::GetParentObject() const noexcept {	
		return _parentObject;
	}

	void Component::RemoveParent() noexcept {
		if (_parentObject == nullptr) {
			return;
		}

		std::string name = _parentObject->GetName();
		_parentObject = nullptr;
		Logger::LogInfo("Obect", name, "was removed");
	}
}

