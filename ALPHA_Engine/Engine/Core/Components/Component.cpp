#include "Component.h"
#include "Core/Objects/Object.h"

namespace Core {
	void Component::UpdateParentObject(Core::Object& newParent) {

	}

	bool Component::CheckAddPossibility(Core::Object& newParent) {
		return true;
	}

	Core::Object* Component::GetParentObject() const noexcept {
		if (_parentsObject.size() > 0) {
			return _parentsObject[0];
		}

		return nullptr;
	}

	const std::vector<Object*>& Component::GetParentsObject() const noexcept {
		return _parentsObject;
	}

	bool Component::RemoveParent(Core::Object& parent) noexcept {
		for (size_t i = 0; i < _parentsObject.size(); i++) {
			if (&parent == _parentsObject[i]) {
				std::string name = _parentsObject[i]->GetName();
				 _parentsObject.erase(_parentsObject.begin() + i);
				 Logger::LogInfo("Obect", name, "was removed");
				 return true;
			}
		}

		Logger::LogError("Parent didn't finded");
		return false;
	}

	void Component::ClearParents() noexcept {
		_parentsObject.clear();
	}
}

