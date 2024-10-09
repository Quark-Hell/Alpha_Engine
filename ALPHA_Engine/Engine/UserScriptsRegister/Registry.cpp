#include "Registry.h"

#include <Core/World.h>

#include "UserScript.h"

#include "Core/Object.h"

//std::vector<Register::UserScript*> Register::Registry::_userScripts{};

std::vector<std::shared_ptr<Register::UserScript>>& Register::Registry::GetUserScripts() {
	static std::vector<std::shared_ptr<Register::UserScript>> _userScripts{};
	return _userScripts;
}

std::unique_ptr<Register::Registry> Register::Registry::MakeRegistry() {
	return std::unique_ptr<Register::Registry>(new Register::Registry);
}

Register::Registry::Registry() {

}

Register::Registry::~Registry() {

}

void Register::Registry::RegistryLoop()
{
	for (size_t i = 0; i < GetUserScripts().size(); i++) {
		if (GetUserScripts()[i] != nullptr) {
			GetUserScripts()[i]->Update();
		}
	}
}

bool Register::Registry::RegisterActorWithComponent(Register::UserScript* script, const std::string& objectName) {
	//Check if script cannot be converted
	if (dynamic_cast<Register::UserScript*>(script) == nullptr)
		return false;
	
	//Later Host will call all UserScript functions
	GetUserScripts().push_back(std::shared_ptr<Register::UserScript>(script));
	std::cout << "Component created" << std::endl;
	return RegisterActor(objectName);
}

bool Register::Registry::RegisterActor(const std::string& objectName) {
	Core::Object::CreateObject(objectName);
	return true;
}