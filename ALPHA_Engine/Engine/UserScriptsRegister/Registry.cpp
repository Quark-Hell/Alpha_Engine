#include "Registry.h"

#include <Core/World.h>

#include "Core/Factory.h"
#include "Core/Objects/GameObject.h"

#include "UserScript.h"
#include "UserScriptsBuffer.h"

namespace Register {
	Registry::Registry(size_t order) : System({"UserScriptsBuffer"}, order) {};

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
}