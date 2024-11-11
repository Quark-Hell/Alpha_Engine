#include "Registry.h"

#include "Core/Factory.h"

#include "UserScript.h"

#include "Core/Object.h"

Register::Registry* Register::Registry::GetInstance() {
	static Register::Registry reg;
	return &reg;
}

void Register::Registry::LoadRegistryBuffer(std::list<std::unique_ptr<Core::Component>>* scripts) {
	_scripts = scripts;
}

void Register::Registry::RegistryLoop() const {
	for (auto& it : *_scripts) {
		auto* userScript = static_cast<UserScript*>(it.get());

		if (userScript->_isStarted == false) {
			userScript->Start();
			userScript->_isStarted = true;
		}

		userScript->Update();
	}
}

bool Register::Registry::RegisterActorWithComponent(Register::UserScript* script, const std::string& objectName) {
	if (script == nullptr) {
		return false;
	}

	
	//Later Host will call all UserScript functions
	auto component = Core::Factory::CreateUserScript(script);
	Core::Object* obj = Core::Factory::CreateObject();
	obj->AddComponent(component);
	return true;
}