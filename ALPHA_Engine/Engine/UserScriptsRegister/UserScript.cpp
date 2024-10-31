#include "UserScript.h"
#include "BaseConfig.h"
#include "Registry.h"

Register::UserScript::UserScript() {
	std::cout << "Info: Creating new component" << std::endl;
	Register::Registry::RegisterActorWithComponent(this);
}

Register::UserScript::~UserScript() {
	std::cout << "Info: Script deleted successfully" << std::endl;
}


void Register::UserScript::Start()  {
	std::cout << "Info: Base start, function can be redefined" << std::endl;
}
void Register::UserScript::Update() {
	std::cout << "Info: Base update, function can be redefined" << std::endl;
}
void Register::UserScript::End() {
	std::cout << "Info: Base end, function can be redefined" << std::endl;
}
