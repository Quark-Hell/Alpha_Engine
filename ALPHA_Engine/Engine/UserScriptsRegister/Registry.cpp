#include "UserScriptsRegister/Registry.h"
#include "UserScriptsRegister/UserScript.h"

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