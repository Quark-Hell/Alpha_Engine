#include "UserScriptsRegister/Registry.h"
#include "UserScriptsRegister/UserScript.h"

#include "Core/Object.h"

std::unique_ptr<Register::Registry> Register::Registry::MakeRegistry() {
	return std::unique_ptr<Register::Registry>(new Register::Registry);
}

Register::Registry::Registry() {

}

Register::Registry::~Registry() {

}

void Register::Registry::RegistryLoop()
{
	for (size_t i = 0; i < _userScripts.size(); i++) {
		if (_userScripts[i] != nullptr) {
			//_userScripts[i]->Update();
		}
	}
}

bool Register::Registry::RegisterActorWithComponent(Register::UserScript* script, std::string objectName) {
	//Check if script cannot be converted
	//if (dynamic_cast<Register::UserScript*>(script) == nullptr)
	//	return false;

	//Later Host will call all UserScript functions
	//_userScripts.push_back(std::unique_ptr<Register::UserScript>(script));
	
	RegisterActor(objectName);
}

bool Register::Registry::RegisterActor(std::string objectName) {
	//Don't care about raw pointer
	//We don't need object in register
	//Object will be added in World inside the constructor of object
	Core::Object* newObject = new Core::Object();
	newObject->SetName(objectName);
}