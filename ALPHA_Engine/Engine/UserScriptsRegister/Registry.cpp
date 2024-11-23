#include "Registry.h"

#include <Core/World.h>

#include "Core/Factory.h"
#include "Core/Object.h"

#include "UserScript.h"
#include "UserScriptsBuffer.h"

namespace Register {
	Registry::Registry() : System({"UserScriptsBuffer"}, 100) {};

	void Registry::EntryPoint(std::vector<Core::SystemData*>& data) {
		auto* buffer = reinterpret_cast<UserScriptsBuffer*>(data[0]);

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
			Core::Logger::LogError("First argument was null: " + __LOGERROR__);
			return false;
		}
		auto* scriptsBuffer = Core::World::GetSystemData("UserScriptsBuffer");
		if (scriptsBuffer == nullptr) {
			Core::Logger::LogError("Script buffer was null: " + __LOGERROR__);
			return false;
		}
		auto* buffer = reinterpret_cast<UserScriptsBuffer*>(scriptsBuffer);

		const auto component = buffer->CreateUserScript(script);
		Core::Object* obj = Core::Factory::CreateObject();
		obj->AddComponent(component);
		obj->SetName(objectName);
		return true;
	}
}