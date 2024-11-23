#include "UserScript.h"
#include "Registry.h"

#include "Core/Logger/Logger.h"

Register::UserScript::UserScript() {
	Core::Logger::LogInfo("Creating new user script");
	Registry::RegisterActorWithComponent(this);
}

Register::UserScript::~UserScript() {
	Core::Logger::LogInfo("Script deleted successfully");
}


void Register::UserScript::Start()  {

}
void Register::UserScript::Update() {

}
void Register::UserScript::End() {

}
