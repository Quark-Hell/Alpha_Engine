#include "Registry.h"

#include "Core/Factory.h"
#include "Core/Object.h"

#include "UserScript.h"
#include "UserScriptsBuffer.h"

namespace Register {
	Registry::Registry() : System({"UserScriptsBuffer"}, 100) {};

	Registry* Registry::GetInstance() {
		static Register::Registry reg;
		return &reg;
	}

	void Registry::EntryPoint(Core::SystemData& data) {
		auto* buffer = dynamic_cast<UserScriptsBuffer*>(&data);
		if (buffer == nullptr) {
			return;
		}

		for (size_t i = 0; i < buffer->GetAllData().size(); i++) {
			auto& component = buffer->GetData(i);

			if (component._isStarted == false) {
				component.Start();
				component._isStarted = true;
			}

			component.Update();
		}
	}

	bool Registry::RegisterActorWithComponent(UserScript* script, const std::string& objectName) {
		if (script == nullptr) {
			return false;
		}

		const auto component = UserScriptsBuffer::CreateUserScript(script);
		Core::Object* obj = Core::Factory::CreateObject();
		obj->AddComponent(component);
		obj->SetName(objectName);
		return true;
	}
}