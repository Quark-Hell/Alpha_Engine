#include "UserScript.h"
#include "BaseConfig.h"
#include "Registry.h"

Register::UserScript::UserScript() {
	std::cout << "Creating new component" << std::endl;
	Register::Registry::RegisterActorWithComponent(this);
}

Register::UserScript::~UserScript() {
	std::cout << "Script deleted successfully" << std::endl;
}


void Register::UserScript::Start()  {
	std::cout << "Base start, function can be redefined" << std::endl;
}
void Register::UserScript::Update() {
	std::cout << "Base update, function can be redefined" << std::endl;
}
void Register::UserScript::End() {
	std::cout << "Base end, function can be redefined" << std::endl;
}
