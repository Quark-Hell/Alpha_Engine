#include "Registry.h"

#include <Core/World.h>

#include "UserScript.h"

#include "Core/Object.h"

std::unique_ptr<Register::Registry> Register::Registry::MakeRegistry() {
	return std::unique_ptr<Register::Registry>(new Register::Registry);
}

Register::Registry::Registry() = default;

Register::Registry::~Registry() = default;

void Register::Registry::RegistryLoop(const std::list<std::unique_ptr<Register::UserScript>>* scripts)
{
	const auto list = scripts;
	auto it = std::begin(*list);

	for (size_t i = 0; i < scripts->size(); i++) {
		if (*it != nullptr) {
			if (it->get()->_isStarted == false) {
				it->get()->Start();
				it->get()->_isStarted = true;
			}

			it->get()->Update();
		}

		std::advance(it, 1);
	}
}

bool Register::Registry::RegisterActorWithComponent(Register::UserScript* script, const std::string& objectName) {
	//Check if script cannot be converted
	if (script == nullptr)
		return false;
	
	//Later Host will call all UserScript functions
	auto component = Core::World::CreateUserScript(script);
	component->SetParentObject(Core::Object::CreateObject(objectName));
	std::cout << "Component created" << std::endl;
	return true;
}