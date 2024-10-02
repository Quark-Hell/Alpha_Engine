#include "UserScript.h"
#include "BaseConfig.h"

#include "Registry.h"

Register::UserScript::UserScript(enum Register::UserScriptType type) {
	switch (type)
	{
	case Register::Actor:
		std::cout << "Actor";
		Register::Registry::RegisterActor();
		break;
	case Register::Component:
		std::cout << "Component";
		Register::Registry::RegisterActorWithComponent(this);
		break;
	default:
		break;
	}

	Start();
}

Register::UserScript::~UserScript() {
	std::cout << "I miss you";
	End();
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