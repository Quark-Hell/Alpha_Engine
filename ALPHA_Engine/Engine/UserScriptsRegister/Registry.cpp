#include "Registry.h"
#include "UserScript.h"

#include "Core/Object.h"

//std::vector<Register::UserScript*> Register::Registry::_userScripts{};

std::vector<std::shared_ptr<Register::UserScript>>& Register::Registry::GetUsertScripts() {
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
	for (size_t i = 0; i < GetUsertScripts().size(); i++) {
		if (GetUsertScripts()[i] != nullptr) {
			GetUsertScripts()[i]->Update();
		}
	}
}

bool Register::Registry::RegisterActorWithComponent(Register::UserScript* script, std::string objectName) {
	//Check if script cannot be converted
	if (dynamic_cast<Register::UserScript*>(script) == nullptr)
		return false;
	
	//Later Host will call all UserScript functions
	GetUsertScripts().push_back(std::shared_ptr<Register::UserScript>(script));
	std::cout << GetUsertScripts().size() << std::endl;
	return RegisterActor(objectName);
}

bool Register::Registry::RegisterActor(std::string objectName) {
	//Don't care about raw pointer
	//We don't need object in register
	//Object will be added in World inside the constructor of object
	auto newObject = Core::Object::CreateObject();
	newObject->SetName(objectName);
	return true;
}