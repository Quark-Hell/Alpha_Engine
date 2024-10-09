#include "UserScript.h"
#include "BaseConfig.h"

#include "Registry.h"

Register::UserScript::UserScript(enum Register::UserScriptType type) {
	switch (type)
	{
		case Register::Actor:
		std::cout << "Creating new actor" << std::endl;
		Register::Registry::RegisterActor();
		break;
	case Register::Component:
		std::cout << "Creating new component" << std::endl;
		Register::Registry::RegisterActorWithComponent(this);
		break;
	default:
		break;
	}

	UserScript::Start();
}

Register::UserScript::~UserScript() {
	UserScript::End();
	std::cout << "Script deleted successfully" << std::endl;
}


void Register::UserScript::Start()  {
	std::cout << "Start" << std::endl;
}
void Register::UserScript::Update() {
	std::cout << "Update" << std::endl;
}
void Register::UserScript::End() {
	std::cout << "End" << std::endl;
}
